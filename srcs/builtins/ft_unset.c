/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:36:53 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/06 05:15:31 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_unset_var(t_env **env, const char *name)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !*env || !name)
		return ;
	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur->full_var);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(char **argv, t_shell_state *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		ft_unset_var(&shell->env, argv[i]);
		i++;
	}
	return (0);
}
