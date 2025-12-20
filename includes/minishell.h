/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:50:25 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/20 01:34:21 by bpetrovi         ###   ########.fr       */
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
typedef struct s_ast_node
{
	t_ast_node_type				type;
	union						u_data
	{
		struct					s_identifier
		{
			char				*string_value;
		} identifier;
		struct					s_ast_redirection
		{
			int					type;
			char				*target;
		} redirection;
		struct					s_ast_command
		{
			struct s_ast_node	*args;
			struct s_ast_node	*args_tail;
			long				arg_cnt;
			struct s_ast_node	*redirections;
			struct s_ast_node	*redirections_tail;
		} command;
		struct					s_ast_pipeline
		{
			struct s_ast_node	*cmds;
			long				cmd_cnt;
		} pipeline;
	} data;
	struct s_ast_node			*next;
}								t_ast_node;

// UTILS FUNCTIONS

int		ft_isspace(char c);
char	*ft_strndup(const char *s1, size_t n);

// LEXER FUNCTIONS

int		string_token(char *input, t_token *next_tok);
int		one_char_tokens(char *input, t_token *next_tok);
int		two_char_tokens(char *input, t_token *next_tok);
t_token	*lexer_advance(t_lexer *lex);
t_token	*lexer_peek(t_lexer *lex);

#endif
