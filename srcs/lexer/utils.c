/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:09:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/06 20:49:38 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(t_token_type	type)
{
	if (type == REDIR_OUT || type == REDIR_IN
		|| type == REDIR_HEREDOC || type == REDIR_APPEND)
		return (1);
	return (0);
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
	token = NULL;
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t		i;
	size_t		len;
	char		*dest;

	i = 0;
	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len] && len < n)
		len++;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_token	*create_token_node(void)
{
	t_token	*new;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->type = INVALID_TOKEN;
	return (new);
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
