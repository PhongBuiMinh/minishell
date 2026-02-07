/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/06 14:08:43 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

volatile sig_atomic_t	g_signal_received = 0;

int	main(void)
{
	t_shell_state	shell;
	char			*line;
	t_command_list	*commands;

	// init_shell(&shell);
	// init_signal_handlers();
	shell.exit_status = 0;
	// run_parser_tests();
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
