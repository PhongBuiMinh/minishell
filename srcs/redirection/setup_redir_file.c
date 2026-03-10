/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:00:56 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/10 21:00:59 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redir_out(t_redirection_list *redir)
{
	int	fd;

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

int	setup_redir_file(t_redirection_list *redir)
{
	char	*clean;

	clean = remove_quotes_str(redir->target);
	if (!clean)
		return (-1);
	free(redir->target);
	redir->target = clean;
	if (redir->redir_type == REDIR_OUT || redir->redir_type == REDIR_APPEND)
		return (setup_redir_out(redir));
	return (setup_redir_in(redir->target));
}
