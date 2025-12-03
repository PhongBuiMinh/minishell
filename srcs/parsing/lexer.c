/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:11:07 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/03 22:44:31 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_tok_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !ft_isspace(str[i]))
		i++;
	return (i);
}

void	other_tokens(t_lexer *lexer, t_token *next_tok)
{
	char	*str;
	int		i;

	i = 0;
	str = lexer->input + lexer->pos;
	if (str[0] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (str[0] == '"')
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]) && is_allowed(str[i]))
			i++;
	}
}

t_token_type	one_char_tokens(t_lexer *lexer)
{
	char			a;
	t_token_type	type;

	type = INVALID_TOKEN;
	a = lexer->input[lexer->pos];
	if (a == '(')
		type = LPARENT;
	else if (a == ')')
		type = RPAREN;
	else if (a == '|')
		type = PIPE;
	else if (a == '>')
		type = REDIR_OUT;
	else if (a == '<')
		type = REDIR_IN;
	if (type != INVALID_TOKEN)
		lexer->pos += 1;
	return (type);
}

t_token_type	two_char_tokens(t_lexer *lexer)
{
	char			*str;
	t_token_type	type;

	type = INVALID_TOKEN;
	str = lexer->input + lexer->pos;
	if (ft_strncmp(str, ">>", 2) == 0)
		type = REDIR_OUT_APP;
	else if (ft_strncmp(str, "<<", 2) == 0)
		type = REDIR_HERE;
	else if (ft_strncmp(str, "||", 2) == 0)
		type = OR_OR;
	else if (ft_strncmp(str, "&&", 2) == 0)
		type = AND_AND;
	if (type != INVALID_TOKEN)
		lexer->pos += 2;
	return (type);
}

t_token	*lexer_next(t_lexer *lexer)
{
	t_token	*next_tok;
	int		length;

	next_tok = malloc(sizeof(t_token));
	if (!next_tok)
		return (NULL);
	next_tok->value = NULL;
	while (ft_isspace(lexer->input[lexer->pos]))
		lexer->pos++;
	length = ft_tok_length(lexer->input[pos]);
	if (length == 0)
		t_token_type = EOF_TOKEN;
	else if (length == 1)
		t_token_type = one_char_tokens(&lexer);
	else if (length == 2)
		t_token_type = two_char_tokens;
	if (t_token_type == INVALID_TOKEN)
		other_tokens(&lexer, next_tok);
	return (token_to_return);
}

int	parser(char *line)
{
	t_lexer	lexer;
	t_token	*next_tok;

	lexer.input = line;
	lexer.pos = 0;
	next_tok = lexer_next(&lexer);
	while (next_tok->type != EOF_TOKEN && next_tok->type != INVALID_TOKEN)
	{
		ft_printf("next token type: %i\nnext token value: %s\n-------\n", next_tok->type, next_token->value);
		free(tok->value);
		free(next_tok);
		next_tok = lexer_next();
	}
	return (0);
}
