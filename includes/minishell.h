/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:50:25 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/12 14:14:19 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef enum e_token_type
{
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_APPEND,
	STRING,
	INVALID_TOKEN,
	EOF_TOKEN
}	t_token_type;

typedef enum e_parse_error
{
    PARSE_OK = 0,
    PARSE_ERR_MALLOC,
    PARSE_ERR_UNEXPECTED_TOKEN,
    PARSE_ERR_INVALID_REDIR,
    PARSE_ERR_PIPE_AT_START,
    PARSE_ERR_UNKNOWN
}   t_parse_error;

// LEXER STRUCTS

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_lexer
{
	char			*input;
	int				pos;
}	t_lexer;

typedef enum e_ast_node_type
{
	AST_REDIRECTION,
	AST_CMD,
	AST_PIPELINE,
	AST_IDENTIFIER
}								t_ast_node_type;

// AST Node Structure

typedef struct	s_argument_list
{
	char					*string;
	struct s_argument_list	*next;

}		t_argument_list;

typedef struct	s_redirection_list
{
	int							redir_type;
	char						*target;
	struct s_redirection_list	*next;
}		t_redirection_list;

typedef struct s_command_list
{
	t_argument_list			*args_tail;
	t_argument_list			*args;
	t_redirection_list		*redirs_tail;
	t_redirection_list		*redirs;
	struct s_command_list	*next;
}		t_command_list;


// UTILS FUNCTIONS

	int				ft_isspace(char c);
	char			*ft_strndup(const char *s1, size_t n);
	void			free_token(t_token *token);
	int				is_redirection(t_token_type	type);

	// LEXER FUNCTIONS

int					string_token(char *input, t_token *next_tok, int just_peek, t_token_type *next_tok_type);
int					one_char_tokens(char *input, t_token_type *next_tok_type);
int					two_char_tokens(char *input, t_token_type *next_tok_type);
void				lexer_skip(t_lexer *lex);
t_token_type		lexer_peek(t_lexer *lex);
t_token				*lexer_advance(t_lexer *lex);
t_token				*create_token_node(void);
int					get_next(char *input, t_token *tok,
						int just_peek, t_token_type *type);

	// PARSER FUNCTIONS

int					parser(char *input, t_command_list **first_command);
void				free_all(t_command_list	*commands);
void				set_error(int *error, t_parse_error err_reason);
int					skip_and_expect(t_lexer *lexer, int *error);
t_redirection_list	*create_redir_node(int *error);
t_argument_list		*create_arg_node(int *error);
void				init_command(t_command_list	*command);


#endif