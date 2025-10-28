/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:42:04 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/18 18:28:28 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	i = 0;
	while (*(src + i) != '\0' && dstlen + i < dstsize - 1)
	{
		*(dst + dstlen + i) = *(src + i);
		i++;
	}
	*(dst + dstlen + i) = '\0';
	return (dstlen + srclen);
}
