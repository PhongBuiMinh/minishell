/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:42:02 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/18 15:45:03 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;

	s1len = 0;
	s2len = 0;
	if (s1 != NULL)
		s1len = ft_strlen(s1);
	if (s2 != NULL)
		s2len = ft_strlen(s2);
	str = (char *)ft_calloc(s1len + s2len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (*(s1 + i))
			str[i++] = s1[j++];
	j = 0;
	if (s2)
		while (*(s2 + j))
			str[i++] = s2[j++];
	return (str);
}
