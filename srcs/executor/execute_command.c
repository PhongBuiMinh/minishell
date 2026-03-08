/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/08 06:34:04 by fbui-min         ###   ########.fr       */
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
		return (free(argv), (void)exit(1));
	path = get_exec_path(argv, env_array);
	if (!path)
		exit(127);
	check_exec_path(argv, path, env_array);
	execve(path, argv, env_array);
	perror(argv[0]);
	if (path != argv[0])
		free(path);
	free(env_array);
	free(argv);
	exit(126);
}

void	execute_command(t_exec_info *info)
{
	char	**argv;
	char	*cmd;
	int		builtin_ret;

	setup_pipes(&info->pipe_info);
	if (setup_redirections(info->cmd->redirs, info->shell) < 0)
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
		free_env_list(info->shell->env);
		exit(builtin_ret);
	}
	exec_external(argv, info->shell);
}
