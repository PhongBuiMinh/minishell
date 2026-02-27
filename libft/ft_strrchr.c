/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:06:24 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/19 23:04:19 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	while (*(s + i))
	{
		if (*(s + i) == (unsigned char)c)
			newstr = ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		newstr = ((char *)s + i);
	return (newstr);
}
