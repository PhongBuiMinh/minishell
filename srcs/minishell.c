/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:08:40 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/19 16:45:36 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	t_token			*next_tok;
	t_lexer			*lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (0);
	lex->pos = 0;
	char	*str = "echo '-mf yo | | wassup <<' |  echo file.txt >ho>w its going";
	lex->input = str;
	if (parser(lex->input) == -1)
		return (printf("\nthe input is invalid\n"), -1);
	else
		printf("\nthe input is valid and the process goes on\n");
	next_tok = lexer_advance(lex);
	while (next_tok->type != EOF_TOKEN)
	{
		printf("next token type: %i\nnext token value: %s\n-------\n", next_tok->type, next_tok->value);
		free_token(next_tok);
		next_tok = lexer_advance(lex);
	}
	free(next_tok);
	free(lex);
	return (0);
}
