/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:36:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/25 17:37:27 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_and_connect_string(t_ast_node *command, t_token *token)
{
	t_ast_node	string;
	t_ast_node	redirection;

	if (is_redirection(token->type));
}

int	create_and_connect_redir(t_ast_node *command, t_token *token)
{
	
}

// A function which checks if there are 2 redirection in a row,
// and also iterates trough all of the string/redirection
// tokens in a single command

int	parse_command(t_lexer *lexer, t_ast_node *command)
{
	t_token_type	next_token;
	t_token_type	redir;
	t_token			*token;

	next_token = lexer_peek(lexer);
	while (next_token == STRING || is_redirection(next_token))
	{
		token = lexer_advance(lexer);
		if (!token)
			return (-1);
		next_token = lexer_peek(lexer);
		if (is_redirection(token->type))
		{
			if (next_token != STRING)
				return (-1);
			redir = token->type;
			free_token(token);
			token = lexer_advance(lexer);
			create_and_connect_redir();
		}
		else
			create_and_connect_string();
		free_token(token);
	}
	return (0);
}


// for each command it uses the parse_command() func
// and then it swallows the next pipe operator before using parse command again
// ps aux | grep -i firefox | grep -v grep | awk '{print $2, $11}' | sort -n
//command pipe  command    pipe  command  pipe      command     pipe command EOF

int	parse_pipeline(t_lexer *lexer, t_command_list *command)
{
	t_token_type	next_token;
	t_command_list	*prev_command;

	next_token = lexer_peek(lexer);
	while (1)
	{
		parse_command(lexer, command);
		if (next_token != PIPE)
			return (-1);
		lexer_skip(lexer);
	}
	return (0);
}				

int	parser(char *input)
{
	t_lexer			lexer;
	t_token_type	next_token;
	t_command_list	*command;

	lexer.input = input;
	next_token = lexer_peek(&lexer);
	if (next_token == PIPE)
		return (printf("Syntax error at beggining of line"), -1);
	command = malloc(sizeof(t_command_list));
	if (!command)
		return (-1);
	parse_pipeline(&lexer, command);
	return (0);
}
