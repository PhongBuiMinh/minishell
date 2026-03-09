/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/09 16:59:51 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipe_fds(t_pipe_info *pipe_info)
{
	if (pipe_info->prev_pipe != STDIN_FILENO)
		close(pipe_info->prev_pipe);
	if (!pipe_info->is_last)
	{
		close(pipe_info->pipe_fd[1]);
		pipe_info->prev_pipe = pipe_info->pipe_fd[0];
	}
}

int	fork_command(t_exec_info *info, int i)
{
	pid_t	pid;

	if (!info->pipe_info.is_last)
	{
		if (pipe(info->pipe_info.pipe_fd) < 0)
			return (perror("pipe"), -1);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		set_child_signals();
		free(info->pids);
		execute_command(info);
	}
	info->pids[i] = pid;
	manage_pipe_fds(&info->pipe_info);
	return (0);
}

int	run_pipeline(t_exec_info *info, t_command_list *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		info->cmd = cmds;
		info->pipe_info.is_first = (i == 0);
		info->pipe_info.is_last = (cmds->next == NULL);
		if (fork_command(info, i++) < 0)
			return (-1);
		cmds = cmds->next;
	}
	return (0);
}

int	execute_pipeline(t_command_list *cmds, t_shell_state *shell)
{
	t_exec_info	info;
	int			ret;

	if (!cmds || !shell)
		return (0);
	if (expand_envs(cmds, shell->env, shell->exit_status) < 0)
		return (1);
	ret = handle_single_builtin(cmds, shell);
	if (ret != -1)
		return (ret);
	info = init_exec_info(cmds, shell);
	if (!info.pids)
		return (1);
	set_parent_wait_signals();
	if (run_pipeline(&info, cmds) < 0)
		return (set_interactive_signals(), free(info.pids), 1);
	ret = wait_all_children(info.pids, info.num_cmds);
	return (free(info.pids), set_interactive_signals(), ret);
}
