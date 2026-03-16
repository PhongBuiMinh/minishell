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

char	*get_exec_path(char **argv, char **env_array)
{
	char	*path;

	if (!argv[0] || !argv[0][0]
			|| (argv[0][0] == '.' && !argv[0][1]))
		return ((void)free(env_array), free(argv), NULL);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = find_command_path(argv[0], env_array);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
			return (free(env_array), free(argv), NULL);
		}
		return (path);
	}
	return (argv[0]);
}
