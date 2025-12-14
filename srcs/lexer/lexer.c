/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:11:07 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/08 20:39:48 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	string_token(char *input, t_token *next_tok)
{
	int		i;
	char	quote_char;

	i = 0;
	if (input[i] == '\'' || input[i] == '"')
	{
		quote_char = input[i];
		while (input[++i] != '\0' && input[i] != quote_char)
			;
		if (input[i] == '\0')
			return (next_tok->type = INVALID_TOKEN, 0);
		next_tok->type = STRING;
		next_tok->value = ft_strndup(input, i + 1);
		if (next_tok->value == NULL)
			return (-1);
		return (0);
	}
	while (input[i] != '\0' && !ft_isspace(input[i]))
		i++;
	next_tok->type = STRING;
	next_tok->value = ft_strndup(input, i);
	if (next_tok->value == NULL)
		return (-1);
	return (0);
}

int	one_char_tokens(char *input, t_token *next_tok)
{
	if (*input == '|')
		return (next_tok->type = PIPE, 1);
	else if (*input == '>')
		return (next_tok->type = REDIR_OUT, 1);
	else if (*input == '<')
		return (next_tok->type = REDIR_IN, 1);
	return (0);
}

int	two_char_tokens(char *input, t_token *next_tok)
{
	if (ft_strncmp(input, ">>", 2) == 0)
		return (next_tok->type = REDIR_APPEND, 1);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (next_tok->type = REDIR_HEREDOC, 1);
	return (0);
}

t_token	*lexer_advance(t_lexer *lex)
{
	t_token		*next_tok;

	next_tok = malloc(sizeof(t_token));
	if (!next_tok)
		return (NULL);
	next_tok->value = NULL;
	next_tok->type = INVALID_TOKEN;
	while (ft_isspace(lex->input[lex->pos]))
		lex->pos++;
	if (lex->input[lex->pos] == '\0')
		return (next_tok->type = EOF_TOKEN, next_tok);
	if (two_char_tokens(lex->input + lex->pos, next_tok))
		return (lex->pos += 2, next_tok);
	else if (one_char_tokens(lex->input + lex->pos, next_tok))
		return (lex->pos += 1, next_tok);
	else if (string_token(lex->input + lex->pos, next_tok) == -1)
		return (NULL);
	lex->pos += ft_strlen(next_tok->value);
	return (next_tok);
}

t_token	*lexer_peek(t_lexer *lex)
{
	t_token	*next_tok;
	int		saved_pos;

	saved_pos = lex->pos;
	next_tok = lexer_advance(lex);
	lex->pos = saved_pos;
	return (next_tok);
}
