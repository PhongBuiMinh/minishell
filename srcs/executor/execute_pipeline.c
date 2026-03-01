/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/01 17:48:10 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	child_process(t_exec_info *info)
// {
// 	set_child_signals();
// 	free(info->pids);
// 	execute_command(info);
// }

void	parent_cleanup(t_pipe_info *pipe_info)
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
	parent_cleanup(&info->pipe_info);
	return (0);
}

int	handle_single_builtin(t_command_list *cmds, t_shell_state *shell)
{
	char	**argv;
	int		bltin_status;

	if (!cmds->args)
		return (0);
	argv = args_to_array(cmds->args);
	if (!argv || !argv[0])
		return (free(argv), 0);
	if (is_builtin(argv[0]))
		bltin_status = handle_builtin(argv[0], argv, shell);
	else
		bltin_status = -1;
	free(argv);
	return (bltin_status);
}

int	execute_pipeline(t_command_list *cmds, t_shell_state *shell)
{
	t_exec_info		info;
	t_command_list	*current;
	int				i;
	int				ret;

	current = NULL;
	if (!cmds || !shell)
		return (0);
	expand_envs(cmds, shell->env);
	ret = handle_single_builtin(cmds, shell);
	if (ret != -1)
		return (ret);
	info = init_exec_info(cmds, shell);
	current = cmds;
	i = 0;
	while (current)
	{
		info.cmd = current;
		info.pipe_info.is_first = (i == 0);
		info.pipe_info.is_last = (current->next == NULL);
		if (fork_command(&info, i) < 0)
			return (free(info.pids), 1);
		current = current->next;
		i++;
	}
	ret = wait_all_children(info.pids, info.num_cmds);
	return (free(info.pids), ret);
}
