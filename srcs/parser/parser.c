/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:36:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/18 23:13:39 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

int	is_redirection(t_token_type	type)
{
	if (type == REDIR_OUT || type == REDIR_IN
		|| type == REDIR_HEREDOC || type == REDIR_APPEND)
		return (1);
	return (0);
}

int	parse_command(t_lexer *lexer)
{
	t_token_type	next_token;
	t_token_type	previous_token;
	t_token			*token;

	previous_token = STRING;
	next_token = lexer_peek(lexer);
	if (next_token == PIPE)
		return (-1);
	while (next_token == STRING || is_redirection(next_token))
	{
		if (is_redirection(previous_token) && next_token != STRING)
			return (printf("False Syntax"), -1);
		token = lexer_advance(lexer);
		next_token = lexer_peek(lexer);
		previous_token = token->type;
	}
	return (0);
}

int	parse_pipeline(t_lexer *lexer)
{
	t_token			*token;
	t_token_type	next_token;

	next_token = lexer_peek(lexer);
	if (next_token == PIPE || next_token == INVALID_TOKEN)
		return (-1);
	while (next_token != EOF_TOKEN)
	{
		if (parse_command(lexer) == -1)
			return (-1);
		next_token = lexer_peek(lexer);
		if (next_token == PIPE)
		{
			token = lexer_advance(lexer);
			free_token(token);
		}
		next_token = lexer_peek(lexer); // can be done better(for tomorrow)
	}
	return (0);
}

int	parser(char *input)
{
	t_lexer		lexer;
	//t_ast_node	*pipeline;

	//pipeline = malloc(sizeof(t_ast_node));
	//if (!pipeline)
	//	return (-1);
	//pipeline->type = AST_PIPELINE;
	//pipeline->data.pipeline.cmd_cnt = 0;
	lexer.pos = 0;
	lexer.input = input;
	if (parse_pipeline(&lexer) == -1)
		return (-1);
	return (0);
}
