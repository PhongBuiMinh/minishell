/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2025/12/20 09:12:12 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int builtin_echo(char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int builtin_cd(char **argv, t_env *env)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		path = getenv("HOME");
	else
		path = argv[1];
	if (!path || getcwd(cwd, sizeof(cwd)) == NULL || chdir(path) != 0)
		return (perror("cd"), 1);
	update_env(env, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env(env, "PWD", cwd);
	return (0);
}

int builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("pwd"), 1);
	printf("%s\n", cwd);
	return (0);
}

// builtin_export - Export environment variables or list them
int builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*equal;

	i = 1;
	if (!argv[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (equal)
		{
			*equal = '\0';
			if (is_valid_identifier(argv[i]))
				add_or_update_env(env, argv[i], equal + 1);
			else
				printf("export: `%s': not a valid identifier\n", argv[i]);
			*equal = '=';
		}
		i++;
	}
	return (0);
}

// builtin_unset - Remove environment variables
int builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			printf("unset: `%s': not a valid identifier\n", argv[i]);
			return (1);
		}
		remove_from_env(env, argv[i]);
		i++;
	}
	return (0);
}
