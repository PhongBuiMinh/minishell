/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 20:56:44 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define PATH_MAX 4096

# include <sys/types.h>
# include "shell.h"

/* forward declarations */
typedef struct s_env				t_env;
typedef struct s_command_list		t_command_list;
typedef struct s_argument_list		t_argument_list;
typedef struct s_redirection_list	t_redirection_list;

typedef struct s_pipe_info
{
	int							pipe_fd[2];
	int							prev_pipe;
	int							is_first;
	int							is_last;
}								t_pipe_info;

typedef struct s_exec_info
{
	t_command_list				*cmd;
	t_shell_state				*shell;
	t_pipe_info					pipe_info;
	pid_t						*pids;
	int							num_cmds;
}								t_exec_info;

/* execution */
void							execute_command(t_exec_info *info);
int								execute_pipeline(t_command_list *commands,
									t_shell_state *shell);
int								count_commands(t_command_list *commands);
int								wait_all_children(pid_t *pids, int num_cmds);

/* builtins */
int								is_builtin(const char *cmd);
int								handle_builtin(char *cmd, char **argv,
									t_shell_state *shell);
/* utils */
int								ft_strcmp(const char *s1, const char *s2);
char							**args_to_array(t_argument_list *args);
char							*find_command_path(char *cmd, char **env_array);
t_exec_info						init_exec_info(t_command_list *cmds,
									t_shell_state *shell);

/* redir */
int								setup_redirections(t_redirection_list *redirs);

#endif