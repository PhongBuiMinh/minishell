/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 10:38:35 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/28 21:34:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cmd_list_to_exec(t_command_list *cmd, t_cmd_exec *exec_cmd)
{
	t_argument_list	*arg;
	int			i;

	if (!cmd || !exec_cmd)
		return (-1);
	ft_memset(exec_cmd, 0, sizeof(t_cmd_exec));
	arg = cmd->args;
	i = 0;
	while (arg && i < MAX_ARGS)
	{
		exec_cmd->argv[i] = arg->string;
		i++;
		arg = arg->next;
	}
	exec_cmd->argv[i] = NULL;
	exec_cmd->redirs = cmd->redirs;
	return (0);
}

int	execute_simple_command(t_command_list *cmd, t_executor *exec)
{
	t_cmd_exec	exec_cmd;
	int			status;

	if (!cmd || !exec)
		return (127);
	if (cmd_list_to_exec(cmd, &exec_cmd) != 0)
		return (127);
	if (!exec_cmd.argv || !exec_cmd.argv[0])
		return (127);
	if (is_builtin(exec_cmd.argv[0]))
		status = execute_builtin(&exec_cmd, exec);
	else
		status = execute_external_command(&exec_cmd, exec);
	return (status);
}

int	execute_ast(t_command_list *commands, t_shell_state *shell)
{
	t_executor		exec;
	t_command_list	*current;
	
	if (!commands || !shell)
		return (127);
	exec.saved_stdin = dup(STDIN_FILENO);
	exec.saved_stdout = dup(STDOUT_FILENO);
	exec.last_exit_status = 0;
	exec.shell = shell;
	current = commands;
	while (current)
	{
		exec.last_exit_status = execute_simple_command(current, &exec);
		current = current->next;
	}
	dup2(exec.saved_stdin, STDIN_FILENO);
	dup2(exec.saved_stdout, STDOUT_FILENO);
	close(exec.saved_stdin);
	close(exec.saved_stdout);
	return (exec.last_exit_status);
}
