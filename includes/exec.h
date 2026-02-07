#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_ARGS 20
# define PATH_MAX 4096

typedef struct s_env
{
	char				*name;
	char				*value;
	char				*full_var;
	struct s_env		*next;
}						t_env;

typedef struct s_pipe_info
{
	int					pipe_fd[2];
	int					prev_pipe;
	int					is_first;
	int					is_last;
}						t_pipe_info;

typedef struct s_shell_state
{
	t_env				*env;
	char				**envp;
	int					exit_status;
}						t_shell_state;

typedef struct s_exec_info
{
	t_command_list		*cmd;
	t_shell_state		*shell;
	t_pipe_info			pipe_info;
	pid_t				*pids;
	int					num_cmds;
}						t_exec_info;

void					execute_command(t_exec_info *info);
int						execute_pipeline(t_command_list *commands,
							t_shell_state *shell);
char					*find_command_path(char *cmd, t_shell_state *shell);
char					**args_to_array(t_argument_list *args);

int						setup_redirections(t_redirection_list *redirs);

int						is_builtin(const char *cmd);
int						handle_builtin(char *cmd, char **argv,
							t_shell_state *shell);
int						ft_cd(char **argv, t_shell_state *shell);
int						ft_echo(char **argv);
int						ft_env(t_shell_state *shell);
int						ft_exit(char **argv, t_shell_state *shell);
int						ft_export(char **args, t_shell_state *shell);
int						ft_pwd(void);
int						ft_unset(char **argv, t_shell_state *shell);

void					update_env(t_env **env_list, char *name, char *value);
t_env					*find_env_var(t_env *env, char *name);
void					add_env_var(t_env **env_list, char *name, char *value);

int						ft_strcmp(const char *s1, const char *s2);


void					run_parser_tests(void);
void					print_cmd_list(t_command_list *commands);

#endif