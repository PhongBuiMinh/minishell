/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 00:03:55 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_commands(t_command_list *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

void	child_process(t_exec_info *info)
{
	free(info->pids);
	execute_command(info);
	exit(1);
}

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
		child_process(info);
	info->pids[i] = pid;
	parent_cleanup(&info->pipe_info);
	return (0);
}

int	wait_all_children(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
	i = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (i == num_cmds - 1)
			{
				if ((status & 0x7F) == 0)
					exit_status = (status >> 8) & 0xFF;
				else
					exit_status = 128 + (status & 0x7F);
			}
		}
		i++;
	}
	return (exit_status);
}

int	execute_pipeline(t_command_list *commands, t_shell_state *shell)
{
	t_exec_info info;
	t_command_list *current;
	int i;

	if (!commands)
		return (0);
	info.shell = shell;
	info.num_cmds = count_commands(commands);
	info.pids = malloc(sizeof(pid_t) * info.num_cmds);
	if (!info.pids)
		return (1);
	info.pipe_info.prev_pipe = STDIN_FILENO;
	current = commands;
	i = -1;
	while (current && ++i >= 0)
	{
		info.cmd = current;
		info.pipe_info.is_first = (i == 0);
		info.pipe_info.is_last = (current->next == NULL);
		if (fork_command(&info, i) < 0)
			return (free(info.pids), 1);
		current = current->next;
	}
	i = wait_all_children(info.pids, info.num_cmds);
	return (free(info.pids), i);
}
