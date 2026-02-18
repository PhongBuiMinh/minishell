/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:28:29 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/12 13:28:31 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	string_token(char *input, t_token *tok, int just_peek, t_token_type *type)
{
	int		i;
	char	quote_char;

	i = 0;
	if (input[i] == '\'' || input[i] == '"')
	{
		quote_char = input[i++];
		while (input[i] && input[i] != quote_char)
			i++;
		if (input[i] == '\0')
			return (*type = INVALID_TOKEN, -2);
		i++;
	}
	else
		while (input[i] && !ft_isspace(input[i]) && input[i] != '|'
			&& input[i] != '<' && input[i] != '>')
			i++;
	*type = STRING;
	if (just_peek)
		return (i);
	tok->value = ft_strndup(input, i);
	if (tok->value == NULL)
		return (-1);
	return (i);
}

int	one_char_tokens(char *input, t_token_type *type)
{
	if (*input == '|')
		return (*type = PIPE, 1);
	else if (*input == '>')
		return (*type = REDIR_OUT, 1);
	else if (*input == '<')
		return (*type = REDIR_IN, 1);
	return (0);
}

int	two_char_tokens(char *input, t_token_type *type)
{
	if (ft_strncmp(input, ">>", 2) == 0)
		return (*type = REDIR_APPEND, 1);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (*type = REDIR_HEREDOC, 1);
	return (0);
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

void	lexer_skip(t_lexer *lex)
{
	t_token_type	type;
	int				len;

	while (ft_isspace(lex->input[lex->pos]))
		lex->pos++;
	if (!lex->input[lex->pos])
		return ;
	len = get_next(lex->input + lex->pos, NULL, true, &type);
	if (len > 0)
		lex->pos += len;
}

t_token_type	lexer_peek(t_lexer *lex)
{
	int				pos;
	t_token_type	type;

	pos = lex->pos;
	while (ft_isspace(lex->input[pos]))
		pos++;
	if (lex->input[pos] == '\0')
		return (EOF_TOKEN);
	get_next(lex->input + pos, NULL, true, &type);
	return (type);
}
