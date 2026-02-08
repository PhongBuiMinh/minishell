/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 19:13:26 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

volatile sig_atomic_t	g_signal_received = 0;

void	init_env_list(t_shell_state *shell, char **envp)
{
	int		i;
	char	*eq_pos;
	char	*name;
	char	*value;

	i = 0;
	shell->env = NULL;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			name = ft_strndup(envp[i], eq_pos - envp[i]);
			value = ft_strdup(eq_pos + 1);
			add_env_var(&shell->env, name, value);
			free(name);
		}
		i++;
	}
}

void	init_shell(t_shell_state *shell, char **envp)
{
	shell->env = NULL;
	shell->exit_status = 0;
	init_env_list(shell, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_state	shell;
	char			*line;
	t_command_list	*commands;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	// init_signal_handlers();
	shell.exit_status = 0;
	while (1)
	{
		if (g_signal_received == SIGINT)
		{
			shell.exit_status = 130;
			g_signal_received = 0;
		}
		else if (g_signal_received == SIGQUIT)
			g_signal_received = 0;
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line != '\0')
			add_history(line);
		commands = NULL;
		if (parser(line, &commands) == 0 && commands != NULL)
		{
			shell.exit_status = execute_pipeline(commands, &shell);
			// free_commands(commands)
		}
		free(line);
	}
	// cleanup_shell(&shell);
	return (shell.exit_status);
}
