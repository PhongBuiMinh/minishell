/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:36:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/13 19:31:46 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	parse_redir(t_lexer *lexer, t_command_list *command,
		t_token_type	token_type, int *error)
{
	t_redirection_list	*new;

	new = create_redir_node(error);
	if (!new)
		return ;
	if (!command->redirs)
		command->redirs = new;
	else
		command->redirs_tail->next = new;
	command->redirs_tail = new;
	new->redir_type = token_type;
	if (!skip_and_expect(lexer, error))
		return ;
	parse_string(lexer, &(new->target), error);
}

void	parse_command(t_lexer *lexer, t_command_list **command,	int *error)
{
	t_token_type	type;

	*command = malloc(sizeof(t_command_list));
	if (!*command)
		return (set_error(error, PARSE_ERR_MALLOC));
	init_command(*command);
	type = lexer_peek(lexer);
	if (type != STRING && !is_redirection(type))
		return (set_error(error, PARSE_ERR_UNEXPECTED_TOKEN));
	while (type == STRING || is_redirection(type))
	{
		if (type == STRING)
			parse_argument(lexer, *command, error);
		else
			parse_redir(lexer, *command, type, error);
		if (*error)
			return ;
		type = lexer_peek(lexer);
	}
}

void	parse_pipeline(t_lexer *lexer, t_command_list **first_command, int *error)
{
	t_command_list	*new_command;
	t_command_list	*prev_command;
	t_token_type	type;

	prev_command = NULL;
	new_command = NULL;
	type = lexer_peek(lexer);
	while (type != EOF_TOKEN)
	{
		parse_command(lexer, &new_command, error);
		if (*error)
			return (printf("error code: %i\n", *error), free_all(new_command));
		if (!prev_command && !(*first_command))
			*first_command = new_command;
		else
			prev_command->next = new_command;
		prev_command = new_command;
		if (lexer_peek(lexer) == PIPE)
			lexer_skip(lexer);
		type = lexer_peek(lexer);
	}
}				

int	parser(char *input, t_command_list **first_command)
{
	t_lexer			lexer;
	t_token_type	next_token;
	int				error;

	error = PARSE_OK;
	lexer.input = input;
	lexer.pos = 0;
	next_token = lexer_peek(&lexer);
	if (next_token == PIPE)
		return (printf("Syntax error at beggining of line"), -1);
	parse_pipeline(&lexer, first_command, &error);
	if (error)
	{
		free_all(*first_command);
		printf("parser error\n");
		return (-1);
	}
	expand_envs(*first_command);
	return (0);
}
