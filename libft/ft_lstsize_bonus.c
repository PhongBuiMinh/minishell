/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:31 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/27 15:04:56 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*traverse;

	count = 0;
	if (!lst)
		return (count);
	traverse = lst;
	while (traverse)
	{
		count++;
		traverse = traverse->next;
	}
	return (count);
}
