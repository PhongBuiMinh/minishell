/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:28:29 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 01:13:49 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	get_next(char *input, t_token *tok,
		int just_peek, t_token_type *type)
{
	if (two_char_tokens(input, type))
		return (2);
	else if (one_char_tokens(input, type))
		return (1);
	return (string_token(input, tok, just_peek, type));
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
