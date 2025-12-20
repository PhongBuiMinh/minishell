/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:36:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/20 01:55:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

int	is_redirection(t_token *next_tok)
{
	if (next_tok->type == REDIR_OUT || next_tok->type == REDIR_IN
		|| next_tok->type == REDIR_HEREDOC || next_tok->type == REDIR_APPEND)
		return (1);
	return (0);
}

s_ast_node	*parse_command(t_lexer *lexer, s_ast_node *previous_command)
{
	t_token		*next_tok;
	s_ast_node	*command;

	command = malloc(sizeof(s_ast_node));
	if (!command)
		return (NULL);
	if (previous_command != NULL)
		previous_command->next = command;
	command->type = AST_CMD;
	next_tok = lexer_peek(lexer);
	while (next_tok == STRING || is_redirection(next_tok))
	{
		free_token(token);
		next_tok = lexer_advance(lexer);
		if (pipeline->cmds == NULL)
			pipeline->cmds = command;
	}
}

int	parser_pipeline(t_lexer *lexer, s_ast_node *pipeline)
{
	t_token		*token;
	s_ast_node	*previous_command;
	s_ast_node	*current_command;

	token = lexer_peek(lexer);
	previous_command = NULL;
	if (token->type == PIPE || token->type == INVALID_TOKEN)
		return (-1);
	while (token->type != TOKEN_EOF)
	{
		free_token(token);
		current_command = parse_command(lexer, previous_command);
		if (pipeline->cmds == NULL)
			pipeline->cmds = current_command;
		previous_command = current_command;
		token = lexer_advance(lexer);
	}
	free(token);
	return (0);
}

s_ast_node	*parser(char *input)
{
	t_lexer		lexer;
	s_ast_node	*pipeline;

	pipeline = malloc(sizeof(s_ast_node));
	if (!pipeline)
		return (NULL);
	pipeline->type = pipeline;
	pipeline->command_cnt = 0;
	lexer->count = 0;
	lexer->input = input;
	parser_pipeline(&lexer, pipeline);
	return (pipeline);
}
