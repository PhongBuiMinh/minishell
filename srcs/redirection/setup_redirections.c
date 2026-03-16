/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:40:24 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/16 03:47:00 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection_list	*find_last_heredoc(t_redirection_list *redirs)
{
	t_redirection_list	*cur;
	t_redirection_list	*last_heredoc;

	cur = redirs;
	last_heredoc = NULL;
	while (cur)
	{
		if (cur->redir_type == REDIR_HEREDOC)
			last_heredoc = cur;
		cur = cur->next;
	}
	return (last_heredoc);
}

int	handle_heredoc_redir(t_redirection_list *cur,
		t_redirection_list *last_heredoc, t_shell_state *shell)
{
	int	tty_fd;

	if (setup_redir_heredoc(cur, shell) < 0)
		return (-1);
	if (cur != last_heredoc)
	{
		tty_fd = open("/dev/tty", O_RDONLY);
		if (tty_fd >= 0)
		{
			dup2(tty_fd, STDIN_FILENO);
			close(tty_fd);
		}
	}
	return (0);
}

int	setup_redirections(t_redirection_list *redirs, t_shell_state *shell)
{
	t_redirection_list	*cur;
	t_redirection_list	*last_heredoc;

	last_heredoc = find_last_heredoc(redirs);
	cur = redirs;
	while (cur)
	{
		if (cur->redir_type == REDIR_HEREDOC)
		{
			if (handle_heredoc_redir(cur, last_heredoc, shell) < 0)
				return (-1);
		}
		else
		{
			if (setup_redir_file(cur) < 0)
			{
				shell->exit_status = 1;
				return (-1);
			}
		}
		cur = cur->next;
	}
	return (0);
}
