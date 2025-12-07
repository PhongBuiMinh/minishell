/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:11:07 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/12/07 16:10:41 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
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

t_token_type	one_char_tokens(char *input, t_token *next_tok)
{
	if (a == '|')
	{
		next_tok->value = NULL;
		next_tok->type = PIPE;
		return (1);
	}
	else if (a == '>')
	{
		next_tok->value = NULL;
		next_tok->type = REDIR_IN;
		return (1);
	}
	else if (a == '<')
	{
		next_tok->value = NULL;
		next_tok->type = REDIR_OUT;
		return (1);
	}
	return (0);
}

t_token_type	two_char_tokens(char *input, t_token *next_tok)
{
	if (ft_strncmp(input, ">>", 2) == 0)
	{
		next_tok->value = NULL;
		next_tok->type = REDIR_APPEND;
	}
	else if (ft_strncmp(input, "<<", 2) == 0)
	{
		next_tok->value = NULL;
		next_tok->type = REDIR_HEREDOC;
	}
	return (type);
}

t_token	*lexer_next(char *input)
{
	t_token		*next_tok;
	int static	i;

	while (ft_isspace(input[i]))
		i++;
	if (two_char_tokens(input + i, next_tok))
		return (next_tok);
	else if (one_char_tokens(input + i, next_tok))
		return (next_tok);

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
