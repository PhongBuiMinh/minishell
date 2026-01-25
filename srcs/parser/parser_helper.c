/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:04:57 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/25 16:26:11 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redirs(t_redirection_list	*redirs)
{
	t_redirection_list	*next_node;

	while (redirs)
	{
		free(redirs->target);
		next_node = redirs->next;
		free(redirs);
		redirs = next_node;
	}
}

void	free_args(t_argument_list	*arguments)
{
	t_argument_list	*next_node;

	while (arguments)
	{
		free(arguments->string);
		next_node = arguments->next;
		free(arguments);
		arguments = next_node;
	}
}

void	free_all(t_command_list	*commands)
{
	t_command_list	*next_node;

	while (commands)
	{
		free_args(commands->arguments);
		free_redirs(commands->redirections);
		next_node = commands->next;
		free(commands);
		commands = next_node;
	}
}