/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:20:51 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/05 12:30:14 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_command_list *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

t_exec_info	init_exec_info(t_command_list *cmds, t_shell_state *shell)
{
	t_exec_info	info;

	info.shell = shell;
	info.num_cmds = count_commands(cmds);
	info.pids = ft_calloc(info.num_cmds, sizeof(pid_t));
	if (!info.pids)
		return (info);
	info.pipe_info.prev_pipe = STDIN_FILENO;
	return (info);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*tmp;
	int		i;

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

int	wait_all_children(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	exit_status;
	int	sig;

	exit_status = 0;
	i = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					ft_putchar_fd('\n', STDOUT_FILENO);
				exit_status = 128 + sig;
			}
			else if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_status);
}
