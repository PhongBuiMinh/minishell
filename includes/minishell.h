/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:50:25 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/14 11:37:53 by fbui-min         ###   ########.fr       */
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
	LPAREN,
	RPAREN,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	REDIR_OUT_APP,
	REDIR_HERE,
	AND_AND,
	OR_OR,
	WORD,
	STRING,
	INVALID_TOKEN,
	EOF_TOKEN
}	t_token_type;

// LEXER STRUCTS

typedef struct s_lexer
{
	char	*input;
	int		pos;
}	t_lexer;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef enum e_ast_node_type
{
	AST_REDIRECTION,
	AST_CMD,
	AST_PIPELINE,
	AST_IDENTIFIER
}								t_ast_node_type;

// AST Node Structure
// typedef struct s_ast_node
// {
// 	t_ast_node_type				type;
// 	union						u_data
// 	{
// 		struct					s_identifier
// 		{
// 			char				*string_value;
// 		} identifier;
// 		struct					s_ast_redirection
// 		{
// 			t_redirection_type	type;
// 			char				*target;
// 		} redirection;
// 		struct					s_ast_command
// 		{
// 			struct s_ast_node	*args;
// 			struct s_ast_node	*args_tail;
// 			long				arg_cnt;
// 			struct s_ast_node	*redirections;
// 			struct s_ast_node	*redirections_tail;
// 		} command;
// 		struct					s_ast_pipeline
// 		{
// 			struct s_ast_node	*cmds;
// 			long				cmd_cnt;
// 		} pipeline;
// 	} data;
// 	struct s_ast_node			*next;
// }								t_ast_node;

#endif
