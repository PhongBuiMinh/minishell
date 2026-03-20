/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 21:00:56 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/16 03:47:00 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_eof_warning(char *delim)
{
	ft_putstr_fd("minishell: warning: heredoc delimited by EOF (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

char	*generate_unique_name(int i)
{
	char	*index_str;
	char	*filename;

	index_str = ft_itoa(i);
	if (!index_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.minishell_heredoc_", index_str);
	free(index_str);
	return (filename);
}

void	assign_heredoc_filenames(t_command_list *cmds)
{
	t_command_list		*cmd_node;
	t_redirection_list	*redir;
	int					i;

	i = 0;
	cmd_node = cmds;
	while (cmd_node)
	{
		redir = cmd_node->redirs;
		while (redir)
		{
			if (redir->redir_type == REDIR_HEREDOC)
				redir->temp_file = generate_unique_name(i++);
			redir = redir->next;
		}
		cmd_node = cmd_node->next;
	}
}

void	unlink_heredocs(t_command_list *cmds)
{
	t_command_list		*curr_cmd;
	t_redirection_list	*redir;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		redir = curr_cmd->redirs;
		while (redir)
		{
			if (redir->redir_type == REDIR_HEREDOC && redir->temp_file != NULL)
			{
				unlink(redir->temp_file);
				free(redir->temp_file);
				redir->temp_file = NULL;
			}
			redir = redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
