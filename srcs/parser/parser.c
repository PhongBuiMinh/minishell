/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:36:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/31 01:22:32 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	init_command(t_command_list	*command)
{
	command->next = NULL;
	command->args = NULL;
	command->args_tail = NULL;
	command->redirs = NULL;
	command->redirs_tail = NULL;
}

void	set_error(int *error)
{
	*error = true;
	return ;
}

void	consume_string(t_lexer *lexer, char **str_pointer, int *error)
{
	t_token	*token_string;
	
	token_string = NULL;
	token_string = lexer_advance(lexer);
	if (!token_string)
		return (set_error(error));
	*str_pointer = ft_strdup(token_string->value);
	free_token(token_string);
	if (!(*str_pointer))
		return (set_error(error));
}

void	consume_argument(t_lexer *lexer, t_command_list *command, int	*error)
{
	t_argument_list	*new_argument;

	new_argument = malloc(sizeof(t_argument_list));
	if (!new_argument)
		return (set_error(error));
	new_argument->string = NULL;
	new_argument->next = NULL;
	if (!command->args)
		command->args = new_argument;
	else
		command->args_tail->next = new_argument;
	command->args_tail = new_argument;
	consume_string(lexer, &(new_argument->string), error);
}

void	consume_redir(t_lexer *lexer, t_command_list *command,
		t_token_type	token_type, int *error)
{
	t_redirection_list	*new_redir;

	new_redir = malloc(sizeof(t_redirection_list));
	if (!new_redir)
		return (set_error(error));
	new_redir->target = NULL;
	new_redir->next = NULL;
	if (!command->redirs)
		command->redirs = new_redir;
	else
		command->redirs_tail->next = new_redir;
	command->redirs_tail = new_redir;
	new_redir->redir_type = token_type;
	lexer_skip(lexer);
	if (lexer_peek(lexer) != STRING)
		return (set_error(error));
	consume_string(lexer, &(new_redir->target), error);
}

void	parse_command(t_lexer *lexer, t_command_list **command,	int *error)
{
	t_token_type	next_token_type;

	*command = malloc(sizeof(t_command_list));
	if (!*command)
		return (set_error(error));
	init_command(*command);
	next_token_type = lexer_peek(lexer);
	if (next_token_type != STRING && !is_redirection(next_token_type))
		return (printf("bug happening here somewhere\n"), set_error(error));
	while (next_token_type == STRING || is_redirection(next_token_type))
	{
		if (next_token_type == STRING)
			consume_argument(lexer, *command, error);
		else
			consume_redir(lexer, *command, next_token_type, error);
		if (*error)
			return ;
		next_token_type = lexer_peek(lexer);
	}
}

void	parse_pipeline(t_lexer *lexer, t_command_list **first_command, int *error)
{
	t_command_list	*new_command;
	t_command_list	*prev_command;
	t_token_type	next_token_type;

	prev_command = NULL;
	new_command = NULL;
	next_token_type = lexer_peek(lexer);
	while (next_token_type != EOF_TOKEN)
	{
		parse_command(lexer, &new_command, error);
		if (*error)
			return (free_all(new_command));
		if (!prev_command && !(*first_command))
			*first_command = new_command;
		else
			prev_command->next = new_command;
		prev_command = new_command;
		if (lexer_peek(lexer) == PIPE)
			lexer_skip(lexer);
		next_token_type = lexer_peek(lexer);
	}
}				

int	parser(char *input, t_command_list **first_command)
{
	t_lexer			lexer;
	t_token_type	next_token;
	int				error;

	error = false;
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
	return (0);
}
