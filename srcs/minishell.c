/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:08:40 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/18 19:34:46 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	t_token	*next_tok;
	t_lexer *lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (0);
	lex->pos = 0;
	char	*str = "echo '-mf yo | wassup <<' file.txt how its going";
	lex->input = str;
	next_tok = lexer_advance(lex);
	while (next_tok->type != TOKEN_EOF)
	{
		printf("next token type: %i\nnext token value: %s\n-------\n", next_tok->type, next_tok->value);
		free(next_tok->value);
		free(next_tok);
		next_tok = lexer_peek(lex);
		printf("next token type peek: %i\n", next_tok->type);
		free(next_tok);
		next_tok = lexer_advance(lex);
	}
	free(next_tok);
	free(lex);
	return (0);
}
