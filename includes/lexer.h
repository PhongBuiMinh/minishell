/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:43:12 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 19:43:30 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	int				pos;
}					t_lexer;

/* lexer utils */
int					ft_isspace(char c);
int					is_redirection(t_token_type type);
void				free_token(t_token *token);

/* lexer core */
int					string_token(char *input, t_token *next_tok, int just_peek,
						t_token_type *next_tok_type);
int					one_char_tokens(char *input, t_token_type *next_tok_type);
int					two_char_tokens(char *input, t_token_type *next_tok_type);
int					get_next(char *input, t_token *tok, int just_peek,
						t_token_type *type);
void				lexer_skip(t_lexer *lex);
t_token_type		lexer_peek(t_lexer *lex);
t_token				*lexer_advance(t_lexer *lex);
t_token				*create_token_node(void);

#endif
