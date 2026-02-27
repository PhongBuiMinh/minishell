/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 16:12:30 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <signal.h>
# include "minishell.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_ARGS 20
# define PATH_MAX 4096

extern volatile sig_atomic_t	g_signal_received;

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

void	init_signal_handlers(void);
void	set_child_signals(void);

int check_unclosed_quotes(const char *str);
char *join_lines(char *old, char *new);
void	init_shell(t_shell_state *shell, char **envp);

// exec functions
void					execute_command(t_exec_info *info);
int						execute_pipeline(t_command_list *commands,
							t_shell_state *shell);
char 					*find_command_path(char *cmd, char **env_array);
char					**args_to_array(t_argument_list *args);
char					**env_to_array(t_env *env);
t_exec_info init_exec_info(t_command_list *cmds, t_shell_state *shell);
int	count_commands(t_command_list *commands);
int	wait_all_children(pid_t *pids, int num_cmds);
char	**args_to_array(t_argument_list *args);
char	**env_to_array(t_env *env);
int	process_signal(t_shell_state *shell, char **full_input);

// redirs
int						setup_redirections(t_redirection_list *redirs);

// builtins
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

// env utils
void					update_env(t_env **env_list, char *name, char *value);
t_env					*find_env_var(t_env *env, char *name);
void					add_env_var(t_env **env_list, char *name, char *value);

int						ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
void	free_env_var(t_env *var);
void					run_parser_tests(void);
void					print_cmd_list(t_command_list *commands);
void					expand_envs(t_command_list *command, t_env *env);

#endif
