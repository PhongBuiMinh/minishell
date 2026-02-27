/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:20:51 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 20:57:11 by bpetrovi         ###   ########.fr       */
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

t_exec_info init_exec_info(t_command_list *cmds, t_shell_state *shell)
{
	t_exec_info	info;

	info.shell = shell;
	info.num_cmds = count_commands(cmds);
	info.pids = malloc(sizeof(pid_t) * info.num_cmds);
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

	exit_status = 0;
	i = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (i == num_cmds - 1)
			{
				if ((status & 0x7F) == 0)
					exit_status = (status >> 8) & 0xFF;
				else
					exit_status = 128 + (status & 0x7F);
			}
		}
		i++;
	}
	return (exit_status);
}
