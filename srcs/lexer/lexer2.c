/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:54:15 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 01:19:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_quotes(char *s, char *quote_char)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			*quote_char = s[i];
			return (1);
		}
		i++;
	}
	return (0);
}

static int	get_str_len(char *input)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (quote == 0)
		{
			if (input[i] == '\'' || input[i] == '"')
				quote = input[i];
			else if (ft_isspace(input[i]) || input[i] == '|'
				|| input[i] == '<' || input[i] == '>')
				break ;
		}
		else
		{
			if (input[i] == quote)
				quote = 0;
		}
		i++;
	}
	return (i);
}

int	string_token(char *input, t_token *tok, int just_peek, t_token_type *type)
{
	int	len;

	len = get_str_len(input);
	*type = STRING;
	if (just_peek)
		return (len);
	tok->value = ft_strndup(input, len);
	if (tok->value == NULL)
		return (-1);
	return (len);
}

t_token	*lexer_advance(t_lexer *lex)
{
	t_token		*tok;
	int			len;

	tok = create_token_node();
	if (!tok)
		return (NULL);
	while (ft_isspace(lex->input[lex->pos]))
		lex->pos++;
	if (!lex->input[lex->pos])
		return (tok->type = EOF_TOKEN, tok);
	len = get_next(lex->input + lex->pos, tok, false, &tok->type);
	if (len == -2)
		return (free(tok), NULL);
	else if (len == -1)
		return (free(tok), NULL);
	lex->pos += len;
	return (tok);
}
