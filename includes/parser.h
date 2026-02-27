/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:43:41 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 20:09:28 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_parse_error
{
	PARSE_OK = 0,
	PARSE_ERR_MALLOC,
	PARSE_ERR_UNEXPECTED_TOKEN,
	PARSE_ERR_INVALID_REDIR,
	PARSE_ERR_PIPE_AT_START,
	PARSE_ERR_UNKNOWN
}								t_parse_error;

typedef struct s_argument_list
{
	char						*string;
	struct s_argument_list		*next;
}								t_argument_list;

typedef struct s_redirection_list
{
	int							redir_type;
	char						*target;
	struct s_redirection_list	*next;
}								t_redirection_list;

typedef struct s_command_list
{
	t_argument_list				*args;
	t_argument_list				*args_tail;
	t_redirection_list			*redirs;
	t_redirection_list			*redirs_tail;
	struct s_command_list		*next;
}								t_command_list;

/* parser */
int								parser(char *input,
									t_command_list **first_command);
void							free_all(t_command_list *commands);
void							init_command(t_command_list *command);
void							set_error(int *error, t_parse_error err_reason);
t_argument_list					*create_arg_node(int *error);
t_redirection_list				*create_redir_node(int *error);
char							*ft_strndup(const char *s1, size_t n);

#endif
