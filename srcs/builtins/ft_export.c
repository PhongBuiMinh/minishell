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

int	is_valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*extract_name(char *arg, char *eq_pos)
{
	if (eq_pos)
		return (ft_substr(arg, 0, eq_pos - arg));
	return (ft_strdup(arg));
}

static char	*extract_value(char *arg, char *eq_pos, t_shell_state *shell)
{
	char	*value;
	t_env	*existing;

	if (eq_pos)
		return (ft_strdup(eq_pos + 1));
	existing = find_env_var(shell->env, arg);
	if (existing && existing->value)
		value = ft_strdup(existing->value);
	else
		value = NULL;
	return (value);
}

int	process_export_arg(char *arg, t_shell_state *shell)
{
	char	*name;
	char	*value;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	name = extract_name(arg, eq_pos);
	if (!name)
		return (1);
	value = extract_value(arg, eq_pos, shell);
	if (eq_pos && !value)
		return (free(name), 1);
	update_env(&shell->env, name, value);
	free(name);
	if (value)
		free(value);
	return (0);
}

int	ft_export(char **args, t_shell_state *shell)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args[1])
		return (sort_env_list(&shell->env),
			print_export_list(shell->env), 0);
	if (args[1][0] == '-')
		return (ft_putstr_fd("minishell: no options\n", 2), 2);
	i = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else if (process_export_arg(args[i], shell) != 0)
			exit_status = 1;
	}
	return (exit_status);
}
