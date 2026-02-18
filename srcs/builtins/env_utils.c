/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/06 22:16:24 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_env_var(t_env **env_list, char *name, char *value)
{
	t_env	*new_var;
	t_env	*last;

	new_var = malloc(sizeof(t_env));
	if (!new_var || !name)
		return (free(new_var));
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	new_var->full_var = ft_strjoin(name, "=");
	if (!new_var->name || !new_var->full_var || (value && !new_var->value))
		return (free_env_var(new_var));
	if (value)
		new_var->full_var = ft_strjoin_free(new_var->full_var, value);
	new_var->next = NULL;
	if (!*env_list)
		*env_list = new_var;
	else
	{
		last = *env_list;
		while (last->next)
			last = last->next;
		last->next = new_var;
	}
}

void	update_env_value(t_env *env_var, char *new_value)
{
	free(env_var->value);
	env_var->value = ft_strdup(new_value);
	free(env_var->full_var);
	env_var->full_var = ft_strjoin(env_var->name, "=");
	env_var->full_var = ft_strjoin(env_var->full_var, new_value);
}

void	update_env(t_env **env_list, char *name, char *value)
{
	t_env	*env_var;

	env_var = find_env_var(*env_list, name);
	if (env_var)
		update_env_value(env_var, value);
	else
		add_env_var(env_list, name, value);
}
