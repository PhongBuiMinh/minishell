/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:49:57 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/05 19:11:19 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_list(t_env *env)
{
	while (env)
	{
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

int	valid_export_var(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	update_full_var(t_env *env_var, char *new_value)
{
	char	*temp;

	free(env_var->full_var);
	temp = ft_strjoin(env_var->name, "=");
	if (!temp)
		return (-1);
	if (new_value)
		env_var->full_var = ft_strjoin_free(temp, new_value);
	else
		env_var->full_var = temp;
	if (!env_var->full_var)
		return (-1);
	return (0);
}

int	process_export_arg(char *arg, t_shell_state *shell)
{
	char	*name;
	char	*value;
	char	*eq_pos;
	t_env	*existing;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (0);
	name = ft_strndup(arg, eq_pos - arg);
	if (!name || !valid_export_var(name))
		return (free(name), 1);
	value = ft_strdup(eq_pos + 1);
	existing = find_env_var(shell->env, name);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
		free(name);
		return (update_full_var(existing, value));
	}
	add_env_var(&shell->env, name, value);
	return (free(name), free(value), 0);
}

int	ft_export(char **args, t_shell_state *shell)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args[1])
		return (sort_env_list(&shell->env),
			print_export_list(shell->env), 0);
	if (args[1][0] == '-' && args[1][1])
		return (ft_putstr_fd("minishell: no option\n", STDERR_FILENO),
			2);
	i = 1;
	while (args[i])
	{
		if (!valid_export_var(args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else if (process_export_arg(args[i], shell) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
