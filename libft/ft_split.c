/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:13:21 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/27 14:24:16 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*strarrfree(char **strarr, size_t maxstr)
{
	size_t	i;

	i = 0;
	while (i < maxstr)
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
	return (NULL);
}

size_t	substrcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

size_t	substrlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	*strgenerate(char const *s, char c)
{
	char	*str;
	size_t	strlen;
	size_t	i;

	strlen = substrlen(s, c);
	str = malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < strlen)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strarr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	strarr = malloc((substrcount(s, c) + 1) * sizeof(char *));
	if (!strarr)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			strarr[j] = strgenerate(&s[i], c);
			if (!strarr[j])
				return (strarrfree(strarr, j));
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	strarr[j] = NULL;
	return (strarr);
}

// int	main(void)
// {
// 	// printf("%li\n", substrcount("abcabc", 'c'));
// 	// printf("%li\n", substrcount("abcab", 'c'));
// 	// printf("%li\n", substrcount("cabcab", 'c'));
// 	// printf("%li\n", substrcount("ccc", 'c'));
// 	// printf("%li\n", substrcount("", 'c'));
// 	// printf("%li\n", substrlen("abff", 'f'));
// 	// printf("%li\n", substrlen("abf", 'f'));
// 	printf("==============================\n");
// 	char **str = ft_split("jabc abbb\n \nbabc ", '\n');
// 	while (*str)
// 	{
// 		printf("%s\n", *str);
// 		str++;
// 	}
// 	return (0);
// }
