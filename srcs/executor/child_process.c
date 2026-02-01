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

int	apply_redirections(t_redir *redirs, t_shell_state *shell)
{
	return (0);
}

// Setup pipeline FDs (stdin from prev, stdout to pipe/orig)
void	setup_child_pipeline(t_command_list *cmd, int inputfd,
								int pipefd[2], t_executor *exec)
{
	if (dup2(inputfd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
	if (cmd->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (dup2(exec->saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(1);
	}
	if (inputfd != STDIN_FILENO)
		close(inputfd);
	close(exec->saved_stdin);
	close(exec->saved_stdout);
}

pid_t	fork_pipeline_child(t_command_list *current, int inputfd,
								int pipefd[2], t_executor *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipeline(current, inputfd, pipefd, exec);
		if (apply_redirections(current->redirs, exec->shell) == -1)
			exit(1);
		if (is_builtin(current->args[0]))
			exit(exec_builtin(current, exec->shell));
		else
			exec_external_cmd(current, exec->shell);
	}
	return (pid);
}
