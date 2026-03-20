/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/10 21:08:33 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define PATH_MAX 4096

# include "shell.h"
# include <sys/types.h>

/* forward declarations */
typedef struct s_env				t_env;
typedef struct s_command_list		t_command_list;
typedef struct s_argument_list		t_argument_list;
typedef struct s_redirection_list	t_redirection_list;

typedef struct s_pipe_info
{
	int								pipe_fd[2];
	int								prev_pipe;
	int								is_first;
	int								is_last;
}									t_pipe_info;

typedef struct s_exec_info
{
	t_command_list					*cmd;
	t_shell_state					*shell;
	t_pipe_info						pipe_info;
	pid_t							*pids;
	int								num_cmds;
}									t_exec_info;

/* execution */
void								execute_command(t_exec_info *info);
int									handle_single_builtin(t_command_list *cmds,
										t_shell_state *shell);
int									execution(t_command_list *commands,
										t_shell_state *shell);
int									count_commands(t_command_list *commands);
int									wait_all_children(pid_t *pids,
										int num_cmds);

/* builtins */
int									is_builtin(const char *cmd);
int									handle_builtin(char *cmd, char **argv,
										t_shell_state *shell);
/* utils */
int									ft_strcmp(const char *s1, const char *s2);
char								**args_to_array(t_argument_list *args);
char								*find_command_path(char *cmd,
										char **env_array);
t_exec_info							init_exec_info(t_command_list *cmds,
										t_shell_state *shell);
int									is_directory(char *path);
void								check_exec_path(char **argv, char *path,
										char **env);
char								*get_exec_path(char **argv,
										char **env_array);

/* redir */
int									setup_redirections(
										t_redirection_list *redirs,
										t_shell_state *shell);
void								unlink_heredocs(t_command_list *cmds);
int									collect_heredocs(t_command_list *cmds,
										t_shell_state *shell);
void								assign_heredoc_filenames(
										t_command_list *cmds);
void								print_eof_warning(char *delim);

#endif
