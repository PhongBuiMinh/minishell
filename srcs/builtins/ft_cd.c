/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:44:56 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/03 18:45:20 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_cd(char **argv, t_shell_state *shell)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		path = ft_getenv(shell->env, "HOME");
	else
		path = argv[1];
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	update_env(&shell->env, "OLDPWD", cwd);
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	update_env(&shell->env, "PWD", cwd);
	return (0);
}
