/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:46:40 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/14 23:01:08 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buffer;
	size_t			i;

	buffer = malloc(count * size);
	i = 0;
	if (buffer == NULL)
		return (NULL);
	while (i < count * size)
	{
		*(buffer + i) = 0;
		i++;
	}
	return ((void *)buffer);
}
