/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:04:57 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 17:59:05 by bpetrovi         ###   ########.fr       */
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
		redirs = NULL;
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
		arguments = NULL;
		arguments = next_node;
	}
}

void	free_all(t_command_list	*commands)
{
	t_command_list	*next_node;

	while (commands)
	{
		free_args(commands->args);
		free_redirs(commands->redirs);
		next_node = commands->next;
		free(commands);
		commands = NULL;
		commands = next_node;
	}
}
