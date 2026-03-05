/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:49:57 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_nodes(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	sort_env_list(t_env **env)
{
	t_env	*curr;
	t_env	*next;
	int		swapped;

	if (!env || !*env)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = *env;
		while (curr && curr->next)
		{
			next = curr->next;
			if (ft_strcmp(curr->name, next->name) > 0)
			{
				swap_env_nodes(curr, next);
				swapped = 1;
			}
			curr = next;
		}
	}
}
