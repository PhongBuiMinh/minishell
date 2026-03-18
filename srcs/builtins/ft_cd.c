/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:44:56 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/08 05:22:44 by fbui-min         ###   ########.fr       */
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

void	update_work_dirs(t_shell_state *shell, char *old_path)
{
	char	new_path[PATH_MAX];

	update_env(&shell->env, "OLDPWD", old_path);
	if (getcwd(new_path, sizeof(new_path)))
		update_env(&shell->env, "PWD", new_path);
}

int	ft_cd(char **argv, t_shell_state *shell)
{
	char	*path;
	char	old_cwd[PATH_MAX];

	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		path = ft_getenv(shell->env, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = ft_getenv(shell->env, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = argv[1];
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (!getcwd(old_cwd, sizeof(old_cwd)))
		old_cwd[0] = '\0';
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	update_work_dirs(shell, old_cwd);
	return (0);
}
