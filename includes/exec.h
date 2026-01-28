#ifndef EXEC_H
#define EXEC_H

# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "minishell.h"

#define MAX_ARGS 20

volatile sig_atomic_t	g_signal_received = 0;

typedef struct s_cmd_exec
{
	char				**argv;
	int					argc;
	t_redirection_list		*redirs;
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

#endif