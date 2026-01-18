/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:49:57 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 21:41:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_export_list(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->name);
		if (env->value)
			printf("=\"%s\"\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

static void	sort_env_list(t_env **env)
{
	t_env	*current;
	t_env	*next;
	int		swapped;
	char	*temp_name;
	char	*temp_value;

	if (!env || !*env)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *env;
		while (current && current->next)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				temp_name = current->name;
				temp_value = current->value;
				current->name = current->next->name;
				current->value = current->next->value;
				current->next->name = temp_name;
				current->next->value = temp_value;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

int	ft_export(char **argv, t_env **env)
{
	int		i;
	char	*equal;
	char	*name_copy;

	i = 1;
	if (!argv[1])
		return (sort_env_list(env), print_export_list(*env), 0);
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (equal)
		{
			name_copy = ft_strndup(argv[i], equal - argv[i]);
			if (is_valid_identifier(name_copy))
				add_or_update_env(env, name_copy, equal + 1);
			else
				printf("export: `%s': not a valid identifier\n", name_copy);
			free(name_copy);
		}
		else if (is_valid_identifier(argv[i]))
			add_or_update_env(env, argv[i], NULL);
		else
			printf("export: `%s': not a valid identifier\n", argv[i]);
		i++;
	}
	return (0);
}
