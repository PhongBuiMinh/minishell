/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 10:38:35 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 14:33:53 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ast_cmd_to_exec(t_ast_node *ast, t_cmd_exec *cmd)
{
	t_ast_node	*arg;
	int			i;

	if (!ast || !cmd || ast->type != AST_COMMAND)
		return (-1);
	ft_memset(cmd, 0, sizeof(t_cmd_exec));
	arg = ast->data.command.args;
	if (arg && arg->type == AST_IDENTIFIER)
		cmd->name = arg->data.identifier.string_value;
	i = 0;
	while (arg && i < MAX_ARGS)
	{
		if (arg->type == AST_IDENTIFIER)
		{
			cmd->argv[i] = arg->data.identifier.string_value;
			cmd->argc++;
			i++;
		}
		arg = arg->next;
	}
	cmd->argv[i] = NULL;
	cmd->redirects = ast->data.command.redirections;
	return (0);
}

int	execute_simple_command(t_ast_node *ast, t_executor *exec)
{
	t_cmd_exec	cmd;
	int			status;

	if (!ast || !exec)
		return (127);
	if (ast_cmd_to_exec(ast, &cmd) != 0)
		return (127);
	// if (apply_redirections(&cmd, exec) != 0)
	// 	return (1);
	if (is_builtin(cmd.name))
		status = execute_builtin(&cmd, exec);
	else
		status = execute_external_command(&cmd, exec);
	// restore_redirections(&exec);
	return (status);
}

int	execute_ast(t_ast_node *ast, t_shell_state *shell)
{
	t_executor	exec;
	
	if (!ast || !shell)
		return (127);
	exec.saved_stdin = dup(STDIN_FILENO);
	exec.saved_stdout = dup(STDOUT_FILENO);
	exec.last_exit_status = 0;
	exec.shell = shell;
	if (ast->type == AST_COMMAND)
		exec.last_exit_status = execute_simple_command(ast, &exec);
	// else if (ast->type == AST_PIPELINE)
	// 	exec.last_exit_status = execute_pipeline(ast, &exec);
	return (exec.last_exit_status);
}
