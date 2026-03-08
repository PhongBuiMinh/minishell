/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:43:48 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 00:44:57 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_and_expect(t_lexer *lexer, int *error)
{
	lexer_skip(lexer);
	if (lexer_peek(lexer) != STRING)
		return (set_error(error, PARSE_ERR_INVALID_REDIR), 0);
	return (1);
}

void	parse_string(t_lexer *lexer, char **str_pointer, int *error)
{
	t_token	*token_string;

	token_string = NULL;
	token_string = lexer_advance(lexer);
	if (!token_string)
		return (set_error(error, PARSE_ERR_MALLOC));
	*str_pointer = ft_strdup(token_string->value);
	free_token(token_string);
	if (!(*str_pointer))
		return (set_error(error, PARSE_ERR_MALLOC));
}

void	parse_argument(t_lexer *lexer, t_command_list *command, int	*error)
{
	t_argument_list	*new;

	new = create_arg_node(error);
	if (!new)
		return ;
	if (!command->args)
		command->args = new;
	else
		command->args_tail->next = new;
	command->args_tail = new;
	parse_string(lexer, &(new->string), error);
}
