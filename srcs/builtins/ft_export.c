/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:49:57 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 02:04:38 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	print_export_list(t_env *env)
// {
// 	while (env)
// 	{
// 		ft_putstr_fd("declare -x ", STDOUT_FILENO);
// 		ft_putstr_fd(env->name, STDOUT_FILENO);
// 		if (env->value)
// 		{
// 			ft_putstr_fd("=\"", STDOUT_FILENO);
// 			ft_putstr_fd(env->value, STDOUT_FILENO);
// 			ft_putstr_fd("\"", STDOUT_FILENO);
// 		}
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		env = env->next;
// 	}
// }

// void	sort_env_list(t_env **env)
// {
// 	t_env	*current;
// 	int		swapped;
// 	char	*temp_name;
// 	char	*temp_value;

// 	if (!env || !*env)
// 		return ;
// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		current = *env;
// 		while (current && current->next)
// 		{
// 			if (ft_strcmp(current->name, current->next->name) > 0)
// 			{
// 				temp_name = current->name;
// 				temp_value = current->value;
// 				current->name = current->next->name;
// 				current->value = current->next->value;
// 				current->next->name = temp_name;
// 				current->next->value = temp_value;
// 				swapped = 1;
// 			}
// 			current = current->next;
// 		}
// 	}
// }

// int	valid_export_var(char *var)
// {
// 	int	i;

// 	i = 0;
// 	if (!ft_isalpha(var[i]) && var[i] != '_')
// 		return (0);
// 	i++;
// 	while (var[i] && var[i] != '=')
// 	{
// 		if (!ft_isalnum(var[i]) && var[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	process_export_arg(char *arg, t_shell_state *shell)
// {
// 	char	*name;
// 	char	*value;
// 	char	*eq_pos;
// 	t_env	*existing;

// 	eq_pos = ft_strchr(arg, '=');
// 	if (!eq_pos)
// 		return (0);
// 	name = ft_strndup(arg, eq_pos - arg);
// 	if (!name || !valid_export_var(name))
// 	{
// 		free(name);
// 		return (1);
// 	}
// 	value = ft_strdup(eq_pos + 1);
// 	existing = find_env_var(shell->env, name);
// 	if (existing)
// 	{
// 		free(existing->value);
// 		existing->value = value;
// 	}
// 	else
// 		add_env_var(&shell->env, name, value);
// 	free(name);
// 	return (0);
// }

int	ft_export(char **args, t_shell_state *shell)
{
	// int	i;
	int	exit_status;

	(void)args;
	(void)shell;
	exit_status = 0;
	// if (!args[1])
	// {
	// 	sort_env_list(&shell->env);
	// 	print_export_list(shell->env);
	// 	return (0);
	// }
	// i = 1;
	// while (args[i])
	// {
	// 	if (!valid_export_var(args[i]))
	// 	{
	// 		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	// 		ft_putstr_fd(args, STDERR_FILENO);
	// 		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	// 		return (1);
	// 	}
	// 	exit_status = process_export_arg(args[i], shell);
	// 	i++;
	// }
	return (exit_status);
}
