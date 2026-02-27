/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:44:56 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 20:35:07 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

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
