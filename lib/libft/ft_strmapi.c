/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:15:41 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/26 18:00:17 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstr;

	newstr = NULL;
	if (s[0] == '\0')
		return (ft_strdup(""));
	newstr = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = (*f)(i, s[i]);
		i++;
	}
	return (newstr);
}
