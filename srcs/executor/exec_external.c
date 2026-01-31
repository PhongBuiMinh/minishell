/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2025/02/31 19:07:42 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// PATH lookup for command
char	*find_command_path(char *cmd, t_shell_state *shell)
{
	return (NULL);
}

// Convert env list → execve array
char	**env_to_array(t_shell_state *shell)
{
	return (NULL);
}

// Final execve - never returns on success
void	exec_external_cmd(t_command_list *cmd, t_shell_state *shell)
{
	char	*cmd_path;
	char	**envp;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(127);
	cmd_path = find_command_path(cmd->argv[0], shell);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	envp = env_to_array(shell);
	if (!envp)
	{
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, cmd->argv, envp);
	perror("minishell: execve");
	free(cmd_path);
	free_array(envp);
	exit(126);
}
