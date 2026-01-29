/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 10:38:35 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/29 14:38:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	save_std_fds(t_executor *exec)
{
	exec->saved_stdin = -1;
	exec->saved_stdout = -1;
	exec->saved_stdin = dup(STDIN_FILENO);
	if (exec->saved_stdin == -1)
		return (perror("dup(STDIN_FILENO)"), -1);
	exec->saved_stdout = dup(STDOUT_FILENO);
	if (exec->saved_stdout == -1)
	{
		close(exec->saved_stdin);
		exec->saved_stdin = -1;
		return (perror("dup(STDOUT_FILENO)"), -1);
	}
	return (0);
}

int	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror("dup2(stdout)"), -1);
	}
	close(pipe_fd[1]);
	return (0);
}

int	restore_and_pipe(int saved_stdout, int pipe_fd[2])
{
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		close(saved_stdout);
		return (perror("dup2(restore stdout)"), -1);
	}
	close(saved_stdout);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		return (perror("dup2(stdin)"), -1);
	}
	close(pipe_fd[0]);
	return (0);
}

void	cleanup_fds(t_executor *exec)
{
	if (exec->saved_stdin >= 0)
	{
		if (dup2(exec->saved_stdin, STDIN_FILENO) == -1)
			perror("minishell: cleanup stdin");
		close(exec->saved_stdin);
		exec->saved_stdin = -1;
	}
	if (exec->saved_stdout >= 0)
	{
		if (dup2(exec->saved_stdout, STDOUT_FILENO) == -1)
			perror("minishell: cleanup stdout");
		close(exec->saved_stdout);
		exec->saved_stdout = -1;
	}
}
