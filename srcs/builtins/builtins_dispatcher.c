/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 21:39:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_builtin(t_cmd_exec *cmd, t_executor *exec)
{
	char	*c;

	if (!cmd || !(c = cmd->argv[0]))
		return (127);
	if (ft_strncmp(c, "echo", 4) == 0 && c[4] == '\0')
		return (ft_echo(cmd->argv));
	if (ft_strncmp(c, "cd", 2) == 0 && c[2] == '\0')
		return (ft_cd(cmd->argv, exec->shell->env));
	if (ft_strncmp(c, "pwd", 3) == 0 && c[3] == '\0')
		return (ft_pwd());
	if (ft_strncmp(c, "exit", 4) == 0 && c[4] == '\0')
		return (ft_exit(cmd->argv, exec->shell));
	if (ft_strncmp(c, "export", 6) == 0 && c[6] == '\0')
		return (ft_export(cmd->argv, &exec->shell->env));
	if (ft_strncmp(c, "unset", 5) == 0 && c[5] == '\0')
		return (ft_unset(cmd->argv, &exec->shell->env));
	if (ft_strncmp(c, "env", 3) == 0 && c[3] == '\0')
		return (ft_env(exec->shell->env));
	return (127);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return ((ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0') ||
		(ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0') ||
		(ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0') ||
		(ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0') ||
		(ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0') ||
		(ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')||
		(ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0'));
}
