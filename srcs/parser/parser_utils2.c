/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:51:33 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/06 20:53:01 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_error(int *error, t_parse_error err_reason)
{
	*error = err_reason;
	return ;
}

int	skip_and_expect(t_lexer *lexer, int *error)
{
	lexer_skip(lexer);
	if (lexer_peek(lexer) != STRING)
		return (set_error(error, PARSE_ERR_INVALID_REDIR), 0);
	return (1);
}

t_redirection_list	*create_redir_node(int *error)
{
	t_redirection_list	*new_redir;

	new_redir = malloc(sizeof(t_redirection_list));
	if (!new_redir)
		return (set_error(error, PARSE_ERR_MALLOC), NULL);
	new_redir->target = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

t_argument_list	*create_arg_node(int *error)
{
	t_argument_list	*new_argument;

	new_argument = malloc(sizeof(t_argument_list));
	if (!new_argument)
		return (set_error(error, PARSE_ERR_MALLOC), NULL);
	new_argument->string = NULL;
	new_argument->next = NULL;
	return (new_argument);
}

void	init_command(t_command_list	*command)
{
	command->next = NULL;
	command->args = NULL;
	command->args_tail = NULL;
	command->redirs = NULL;
	command->redirs_tail = NULL;
}
