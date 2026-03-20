/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:49:57 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/05 12:29:58 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_list(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "_") == 0)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->name, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
}

int	update_full_var(t_env *env_var, char *new_value)
{
	char	*temp;

	if (env_var->full_var)
		free(env_var->full_var);
	if (new_value)
	{
		temp = ft_strjoin(env_var->name, "=");
		if (!temp)
			return (-1);
		env_var->full_var = ft_strjoin_free(temp, new_value);
	}
	else
		env_var->full_var = ft_strdup(env_var->name);
	if (!env_var->full_var)
		return (-1);
	return (0);
}

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
