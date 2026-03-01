/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/01 18:03:36 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes(t_pipe_info *info)
{
	if (!info->is_first)
	{
		dup2(info->prev_pipe, STDIN_FILENO);
		close(info->prev_pipe);
	}
	if (!info->is_last)
	{
		close(info->pipe_fd[0]);
		dup2(info->pipe_fd[1], STDOUT_FILENO);
		close(info->pipe_fd[1]);
	}
}

void	exec_external(char **argv, t_shell_state *shell)
{
	char	**env_array;
	char	*path;

	env_array = env_to_array(shell->env);
	if (!env_array)
	{
		free(argv);
		exit(1);
	}
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = find_command_path(argv[0], env_array);
		if (path)
		{
			execve(path, argv, env_array);
			free(path);
		}
	}
	execve(argv[0], argv, env_array);
	free(env_array);
	free(argv);
	exit(127);
}

void	execute_command(t_exec_info *info)
{
	char	**argv;
	char	*cmd;
	int		builtin_ret;

	setup_pipes(&info->pipe_info);
	if (setup_redirections(info->cmd->redirs) < 0)
		exit(1);
	argv = args_to_array(info->cmd->args);
	if (!argv)
		exit(1);
	if (!argv[0])
	{
		free(argv);
		exit(127);
	}
	cmd = argv[0];
	if (is_builtin(cmd))
	{
		builtin_ret = handle_builtin(cmd, argv, info->shell);
		free(argv);
		exit(builtin_ret);
	}
	exec_external(argv, info->shell);
}
