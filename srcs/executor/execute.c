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

int	exec_single_cmd(t_command_list *cmd, t_shell_state *shell)
{
	t_executor	exec;
	pid_t		pid;
	int			wstatus;

	if (save_std_fds(&exec) == -1)
		return (-1);
	exec.shell = shell;
	if (apply_redirections(cmd->redirs, shell) == -1)
		return (cleanup_fds(&exec), 1);
	if (is_builtin(cmd->args[0]))
	{
		exec.last_exit_status = exec_builtin(cmd, shell);
		cleanup_fds(&exec);
		return (exec.last_exit_status);
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), cleanup_fds(&exec), -1);
	if (pid == 0)
		exec_external_cmd(cmd, shell);
	cleanup_fds(&exec);
	waitpid(pid, &wstatus, 0);
	return (extract_exit_status(wstatus));
}

int	handle_pipe_error(t_executor *exec)
{
	perror("minishell: pipe");
	while (wait(NULL) > 0)
		;
	cleanup_fds(exec);
	return (1);
}

int	handle_fork_error(t_executor *exec, t_command_list *current, int pipefd[2])
{
	perror("minishell: fork");
	if (current->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	while (wait(NULL) > 0)
		;
	cleanup_fds(exec);
	return (1);
}

int	exec_pipeline_cmds(t_command_list *commands, t_executor *exec)
{
	t_command_list	*current;
	int				pipefd[2];
	int				inputfd;
	pid_t			last_pid;
	int				exit_status;

	inputfd = exec->saved_stdin;
	current = commands;
	exit_status = 0;
	while (current)
	{
		if (current->next && pipe(pipefd) == -1)
			return (handle_pipe_error(exec));
		last_pid = fork_pipeline_child(current, inputfd, pipefd, exec);
		if (last_pid == -1)
			return (handle_fork_error(exec, current, pipefd));
		close_and_update_fds(&inputfd, exec->saved_stdin, pipefd, current);
		current = current->next;
	}
	cleanup_fds(exec);
	handle_wait_status(last_pid, &exit_status);
	return (exit_status);
}

int	execute_pipeline(t_command_list *commands, t_shell_state *shell)
{
	t_executor	exec;
	int			exit_status;

	if (!commands || !shell)
		return (127);
	if (!commands->next)
		return (exec_single_cmd(commands, shell));
	if (save_std_fds(&exec) == -1)
		return (-1);
	exec.shell = shell;
	exec.last_exit_status = 0;
	exit_status = exec_pipeline_cmds(commands, &exec);
	return (exit_status);
}
