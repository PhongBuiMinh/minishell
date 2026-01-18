/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 14:37:30 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

typedef struct s_cmd_exec
{
	char				**argv;
	int					argc;
	t_redirection		*redirections;
}	t_cmd_exec;

typedef struct s_executor
{
	int					saved_stdin;
	int					saved_stdout;
	int					last_exit_status;
	t_shell_state		*shell;
}	t_executor;

int	main(void)
{
	t_shell_state	shell;
	char			*line;
	
	init_shell(&shell);
	init_signal_handlers();
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
			break;
		}
		if (parse_line(line, &shell) == 0)
		{
			shell.exit_status = execute_ast(shell.ast, &shell);
			shell.ast = NULL;
		}
		free(line);
	}
	cleanup_shell();
	return (shell.exit_status);
}
