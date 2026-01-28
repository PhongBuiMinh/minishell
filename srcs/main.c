/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/27 19:06:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

typedef struct s_cmd_exec
{
	char				**argv;
	int					argc;
	t_redirection		*redirections;
}						t_cmd_exec;

typedef struct s_executor
{
	int					saved_stdin;
	int					saved_stdout;
	int					last_exit_status;
	t_shell_state		*shell;
}						t_executor;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell_state
{
	t_env				*env;
	int					exit_status;
	t_command_list		*commands;
}						t_shell_state;

int	main(void)
{
	t_shell_state	shell;
	char			*line;
	t_command_list	*commands;

	init_shell(&shell);
	init_signal_handlers();
	shell.exit_status = 0;
	shell.commands = NULL;
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
			shell.exit_status = execute_ast(commands, &shell);
			// free_commands(commands)
		}
		free(line);
	}
	cleanup_shell(&shell);
	return (shell.exit_status);
}
