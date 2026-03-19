/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:36:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/09 00:25:36 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	parse_pipeline(t_lexer *lexer,
	t_command_list **first_command, int *error)
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
			return (free_all(new_command));
		if (!prev_command && !(*first_command))
			*first_command = new_command;
		else
			prev_command->next = new_command;
		prev_command = new_command;
		if (lexer_peek(lexer) == PIPE)
		{
			lexer_skip(lexer);
			type = lexer_peek(lexer);
			if (type == EOF_TOKEN || type == PIPE)
				return (set_error(error, PARSE_ERR_UNEXPECTED_TOKEN));
		}
		type = lexer_peek(lexer);
	}
}

void	handle_parse_error(int error, t_lexer *lexer)
{
	t_token_type	type;

	if (error == 3)
	{
		type = lexer_peek(lexer);
		ft_putstr_fd("minishell: syntax error near unexpected token ",
			STDERR_FILENO);
		if (type == EOF_TOKEN || type == NEWLINE)
			ft_putstr_fd("`newline'\n", STDERR_FILENO);
		else if (type == PIPE)
			ft_putstr_fd("`|'\n", STDERR_FILENO);
		else if (type == REDIR_OUT)
			ft_putstr_fd("`>'\n", STDERR_FILENO);
		else if (type == REDIR_IN)
			ft_putstr_fd("` < '\n", STDERR_FILENO);
		else
			ft_putstr_fd("`syntax error'\n", STDERR_FILENO);
	}
	else if (error == PARSE_ERR_MALLOC)
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
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
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return (-1);
	}
	parse_pipeline(&lexer, first_command, &error);
	if (error)
	{
		handle_parse_error(error, &lexer);
		free_all(*first_command);
		*first_command = NULL;
		return (-1);
	}
	return (0);
}
