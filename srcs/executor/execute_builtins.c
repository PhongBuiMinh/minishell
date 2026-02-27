/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	handle_builtin(char *cmd, char **argv, t_shell_state *shell)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(argv));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(argv, shell));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(argv, shell));
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(argv, shell));
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(argv, shell));
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(shell));
	return (127);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return ((ft_strcmp(cmd, "echo") == 0) || (ft_strcmp(cmd, "cd") == 0)
		|| (ft_strcmp(cmd, "pwd") == 0) || (ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "export") == 0) || (ft_strcmp(cmd, "unset") == 0)
		|| (ft_strcmp(cmd, "env") == 0));
}
// echo, pwd, env = child
