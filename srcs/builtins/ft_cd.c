/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:44:56 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 21:40:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(char **argv, t_env *env)
{
	char	*path;
	char	cwd[PATH_MAX];
	t_env	*home;

	path = NULL;
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		home = find_env_node(env, "HOME");
		if (home)
			path = home->value;
	}
	else
		path = argv[1];
	if (!path)
		return (perror("minishell: cd: HOME not set"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	update_env(&env, "OLDPWD", cwd);
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	update_env(&env, "PWD", cwd);
	return (0);
}
