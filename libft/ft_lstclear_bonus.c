/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:10:00 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/27 15:12:50 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*clear;

	while (*lst)
	{
		clear = *lst;
		*lst = (*lst)->next;
		(*del)(clear->content);
		free(clear);
	}
	free(*lst);
	*lst = NULL;
}
