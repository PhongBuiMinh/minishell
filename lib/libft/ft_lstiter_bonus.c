/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:10:51 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/27 15:11:22 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*traverse;

	if (!lst)
		return ;
	traverse = lst;
	while (traverse)
	{
		(*f)(traverse->content);
		traverse = traverse->next;
	}
}
