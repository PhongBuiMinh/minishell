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

int setup_redir_out(t_redirection_list *redir)
{
    int fd;
    
    if (redir->redir_type == REDIR_OUT)
        fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return (perror(redir->target), -1);
    if (dup2(fd, STDOUT_FILENO) < 0)
        return (close(fd), perror("dup2"), -1);
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
		return (close(fd), perror("dup2"), -1);
	close(fd);
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
			return (0);
		redirs = redirs->next;
    }
	return (0);
}
