/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2025/12/29 07:18:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!(isalpha(*str) || *str == '_'))
		return (0);
	while (*++str)
		if (!(isalnum(*str) || *str == '_'))
			return (0);
	return (1);
}

int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_env	*find_env_node(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_or_update_env(t_env **env, const char *name, const char *value)
{
	t_env	*node;
	t_env	*new;

	node = find_env_node(*env, name);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

void	remove_from_env(t_env **env, const char *name)
{
	t_env *current;
	t_env *prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
