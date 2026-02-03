/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/03 19:13:44 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void exec_external(char **argv, t_shell_state *shell)
// {
// 	char	*path;

// 	if (execve(argv[0], argv))
// }

char	**args_to_array(t_argument_list *args)
{
	int				i;
	int				count;
	char			**argv;
	t_argument_list	*tmp;

	count = 0;
	tmp = args;
	while (tmp && ++count)
		tmp = tmp->next;
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (args)
	{
		argv[i] = args->string;
		args = args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

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

void	execute_command(t_exec_info *info)
{
	char	**argv;
	char	*cmd;
	int		builtin_ret;

	setup_pipes(&info->pipe_info);
	// if (setup_redirections() < 0)
	// 	exit(1);
	argv = args_to_array(info->cmd->args);
	if (!argv || !argv[0])
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		exit(127);
	}
	cmd = argv[0];
	if (is_builtin(cmd))
	{
		builtin_ret = handle_builtin(cmd, argv, info->shell);
		free(argv);
		exit(builtin_ret);
	}
	// exec_external();
}
