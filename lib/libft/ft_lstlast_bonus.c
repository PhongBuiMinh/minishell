/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:05:58 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/27 15:06:34 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*traverse;

	traverse = lst;
	while (traverse)
	{
		if (traverse->next == NULL)
			return (traverse);
		traverse = traverse->next;
	}
	return (traverse);
}
