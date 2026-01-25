/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:09:03 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/19 18:07:11 by bpetrovi         ###   ########.fr       */
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
