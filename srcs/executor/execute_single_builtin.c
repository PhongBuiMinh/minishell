/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/07 23:14:45 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	handle_single_builtin(t_command_list *cmds, t_shell_state *shell)
{
	char	**argv;
	int		status;
	int		saved_stdin;
	int		saved_stdout;

	if (cmds->next)
		return (-1);
	argv = args_to_array(cmds->args);
	if (argv && argv[0] && !is_builtin(argv[0]))
		return (free(argv), -1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(cmds->redirs, shell) < 0)
		return (free(argv), restore_fds(saved_stdin, saved_stdout),
			shell->exit_status);
	status = 0;
	if (argv && argv[0])
		status = handle_builtin(argv[0], argv, shell);
	free(argv);
	restore_fds(saved_stdin, saved_stdout);
	return (status);
}
