/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:50:25 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/03 20:33:37 by bpetrovi         ###   ########.fr       */
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

#endif
