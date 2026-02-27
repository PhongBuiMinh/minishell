/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:40:24 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 17:51:47 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	setup_redir_out(t_redirection_list *redir)
{
	int fd;

	if (redir->redir_type == REDIR_OUT)
		fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->target), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), -1);
	close(fd);
	return (0);
}

int	setup_redir_in(char *target)
{
	int	fd;

	fd = open(target, O_RDONLY);
	if (fd < 0)
		return (perror(target), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), -1);
	close(fd);
	return (0);
}

void	read_heredoc(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(write_fd);
			exit(0);
		}
		ft_putendl_fd(line, write_fd);
		free(line);
		if (g_signal_received == SIGINT)
		{
			close(write_fd);
			exit(130);
		}
	}
}

int setup_redir_heredoc(t_redirection_list *redir)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
	{
		rl_catch_signals = 0;
		set_child_signals();
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
		read_heredoc(fd[1], redir->target);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (close(fd[0]), -1);
	close(fd[0]);
	return (0);
}

int	setup_redirections(t_redirection_list *redirs)
{
	while (redirs)
	{
		if (redirs->redir_type == REDIR_OUT
			|| redirs->redir_type == REDIR_APPEND)
		{
			if (setup_redir_out(redirs) < 0)
				return (-1);
		}
		else if (redirs->redir_type == REDIR_IN)
		{
			if (setup_redir_in(redirs->target) < 0)
				return (-1);
		}
		else if (redirs->redir_type == REDIR_HEREDOC)
		{
			if (setup_redir_heredoc(redirs) < 0)
				return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}
