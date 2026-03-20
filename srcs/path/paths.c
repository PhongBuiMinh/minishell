/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 06:34:14 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/08 06:34:28 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
		return (closedir(dir), 1);
	return (0);
}

void	check_exec_path(char **argv, char *path, char **env)
{
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (path != argv[0])
			free(path);
		return (free(env), free(argv), (void)exit(127));
	}
	if (is_directory(path))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		if (path != argv[0])
			free(path);
		return (free(env), free(argv), (void)exit(126));
	}
}

static char	*find_path_logic(char *cmd, char **env_array)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_command_path(cmd, env_array));
}

char	*get_exec_path(char **argv, char **env_array)
{
	char	*path;

	if (!argv[0] || !argv[0][0]
		|| ft_strcmp(argv[0], ".") == 0 || ft_strcmp(argv[0], "..") == 0)
	{
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (NULL);
	}
	path = find_path_logic(argv[0], env_array);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (path);
}

// static char	*find_path_logic(char *cmd, char **env_array)
// {
// 	char	*path;
// 	char	*cwd;

// 	if (ft_strchr(cmd, '/'))
// 		return (ft_strdup(cmd));
// 	path = find_command_path(cmd, env_array);
// 	if (!path)
// 	{
// 		cwd = getcwd(NULL, 0);
// 		path = build_path(cwd, cmd);
// 		free(cwd);
// 		if (access(path, F_OK | X_OK) != 0)
// 		{
// 			free(path);
// 			return (NULL);
// 		}
// 	}
// 	return (path);
// }
