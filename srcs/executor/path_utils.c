/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:33:23 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 18:21:09 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_free_paths(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*tmp;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		array[i++] = tmp->full_var;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

// char	*get_path_env(t_shell_state *shell)
// {
// 	char	**env_array;
// 	char	*path_env;
// 	int		i;

// 	env_array = env_to_array(shell->env);
// 	if (!env_array)
// 		return (NULL);
// 	i = 0;
// 	while (env_array[i])
// 	{
// 		if (ft_strncmp(env_array[i], "PATH=", 5) == 0)
// 		{
// 			path_env = ft_strdup(env_array[i] + 5);
// 			free(env_array);
// 			return (path_env);
// 		}
// 		i++;
// 	}
// 	free(env_array);
// 	return (NULL);
// }

char	*build_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (ft_free_paths(paths), full_path);
		free(full_path);
		i++;
	}
	ft_free_paths(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, char **env_array)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_env = NULL;
	while (env_array[i])
	{
		if (ft_strncmp(env_array[i], "PATH=", 5) == 0)
		{
			path_env = env_array[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = search_in_paths(paths, cmd);
	return (full_path);
}
