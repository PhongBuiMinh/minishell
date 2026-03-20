/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:36:53 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!argv[1])
		return (0);
	if (argv[1][0] == '-')
		return (ft_putstr_fd("minishell: unset: no options\n", 2), 2);
	i = 0;
	while (argv[++i])
		ft_unset_var(&shell->env, argv[i]);
	return (0);
}
