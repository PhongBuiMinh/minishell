/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:46:37 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/18 15:52:34 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	newstr = (char *)ft_calloc(len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (i < len)
	{
		*(newstr + i) = *(s + start + i);
		i++;
	}
	return (newstr);
}
