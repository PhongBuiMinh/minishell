/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:11:07 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/28 02:13:19 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	string_token(char *input, t_token *next_tok, int just_peek, t_token_type *next_tok_type)
{
	int		i;
	char	quote_char;

	i = 0;
	if (input[i] == '\'' || input[i] == '"')
	{
		quote_char = input[i];
		i += 1;
		while (input[i] && input[i] != quote_char)
			i++;
		if (input[i] == '\0')
			return (*next_tok_type = INVALID_TOKEN, 0);
	}
	else
		while (input[i] && !ft_isspace(input[i]))
			i++;
	*next_tok_type = STRING;
	if (just_peek)
		return (i);
	next_tok->value = ft_strndup(input, i);
	if (next_tok->value == NULL)
		return (-1);
	return (0);
}

int	one_char_tokens(char *input, t_token_type *next_tok_type)
{
	if (*input == '|')
		return (*next_tok_type = PIPE, 1);
	else if (*input == '>')
		return (*next_tok_type = REDIR_OUT, 1);
	else if (*input == '<')
		return (*next_tok_type = REDIR_IN, 1);
	return (0);
}

int	two_char_tokens(char *input, t_token_type *next_tok_type)
{
	if (ft_strncmp(input, ">>", 2) == 0)
		return (*next_tok_type = REDIR_APPEND, 1);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (*next_tok_type = REDIR_HEREDOC, 1);
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
	if (two_char_tokens(lex->input + lex->pos, &(next_tok->type)))
		return (lex->pos += 2, next_tok);
	else if (one_char_tokens(lex->input + lex->pos, &(next_tok->type)))
		return (lex->pos += 1, next_tok);
	else if (string_token(lex->input + lex->pos, next_tok, false, &(next_tok->type)) == -1)
		return (NULL);
	if (next_tok->value)
		lex->pos += ft_strlen(next_tok->value);
	return (next_tok);
}

void	lexer_skip(t_lexer *lex)
{
	t_token_type	next_token_type;

	next_token_type = INVALID_TOKEN;
	while (ft_isspace(lex->input[lex->pos]))
		lex->pos++;
	if (lex->input[lex->pos] == '\0')
		next_token_type = EOF_TOKEN;
	if (two_char_tokens(lex->input + lex->pos, &next_token_type))
		lex->pos += 2;
	else if (one_char_tokens(lex->input + lex->pos, &next_token_type))
		lex->pos += 1;
	else
		lex->pos += string_token(lex->input + lex->pos, NULL, true, &next_token_type);
}

t_token_type	lexer_peek(t_lexer *lex)
{
	t_token_type	next_token_type;
	int				pos;

	next_token_type = INVALID_TOKEN;
	pos = lex->pos;
	while (ft_isspace(lex->input[pos]))
		pos++;
	if (lex->input[pos] == '\0')
		return (next_token_type = EOF_TOKEN, next_token_type);
	if (two_char_tokens(lex->input + pos, &next_token_type))
		return (next_token_type);
	else if (one_char_tokens(lex->input + pos, &next_token_type))
		return (next_token_type);
	else
		string_token(lex->input + pos, NULL, true, &next_token_type);
	return (next_token_type);
}
