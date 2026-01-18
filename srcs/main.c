/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 21:42:54 by codespace        ###   ########.fr       */
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
	t_ast_node			*ast;
}						t_shell_state;

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
			break ;
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
