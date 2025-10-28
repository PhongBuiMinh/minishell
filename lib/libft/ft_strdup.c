/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:03:21 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/14 23:23:48 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + 1);
	if (dst == NULL || s1 == NULL)
		return (NULL);
	while (*(s1 + i))
	{
		*((unsigned char *)dst + i) = *((unsigned char *)s1 + i);
		i++;
	}
	*((unsigned char *)dst + i) = '\0';
	return (dst);
}
