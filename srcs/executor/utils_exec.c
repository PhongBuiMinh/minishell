/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2025/02/31 19:07:42 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_exit_status(int wstatus)
{
	if ((wstatus & 0x7F) == 0)
		return ((wstatus >> 8) & 0xFF);
	return (128 + (wstatus & 0x7F));
}

void	handle_wait_status(pid_t last_pid, int *exit_status)
{
	pid_t	finished;
	int		wstatus;

	while ((finished = wait(&wstatus)) != -1)
	{
		if (finished == last_pid)
		{
			*exit_status = extract_exit_status(wstatus);
			if (WIFSIGNALED(wstatus))
			{
				int sig = WTERMSIG(wstatus);
				if (sig == SIGINT)
					ft_putstr_fd("\n", STDERR_FILENO);
				else if (sig == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			}
		}
	}
}

static void	close_and_update_fds(int *inputfd, int saved_stdin, int *pipefd,
								t_command_list *current)
{
	if (*inputfd != saved_stdin)
		close(*inputfd);
	if (current->next)
	{
		close(pipefd[1]);
		*inputfd = pipefd[0];
	}
}

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
