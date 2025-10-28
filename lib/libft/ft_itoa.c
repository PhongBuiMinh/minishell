/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:32:54 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/24 17:01:52 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numlen(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	strlen;
	long	num;
	size_t	i;

	num = n;
	strlen = numlen(n);
	str = ft_calloc(strlen + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
		num *= -1;
	i = 0;
	while (i < strlen)
	{
		str[strlen - 1 - i] = (num % 10) + 48;
		num /= 10;
		i++;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
