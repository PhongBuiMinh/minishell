/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 00:37:15 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Reads lines from stdin until delim is matched or EOF.
** If expand = 1, each line is passed to expand_hd_line before writing.
** expand_hd_line receives a heap-allocated copy of the line and must return
** a heap-allocated expanded string.
** Runs inside the child process — always terminates via exit().
*/
void	read_heredoc(int write_fd, char *delim, int expand,
		t_shell_state *shell)
{
	char	*line;
	char	*exp_line;

	(void)expand;
	(void)shell;
	(void)exp_line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			close(write_fd);
			exit(0);
		}
		//if (expand)
		//{
		//	exp_line = expand_hd_line(ft_strdup(line), shell->env,
		//			shell->exit_status);
		//	if (exp_line)
		//		ft_putendl_fd(exp_line, write_fd);
		//	free(exp_line);
		//}
		//else
		//	ft_putendl_fd(line, write_fd);
		free(line);
	}
}

// Child-side setup: reset signals, close unused pipe end, start reading.
void	setup_heredoc_child(int *fd, char *delim, int expand,
		t_shell_state *shell)
{
	set_child_signals();
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	read_heredoc(fd[1], delim, expand, shell);
}

/*
** Forks a child to collect heredoc input into a pipe
** If the delimiter is quoted (<< 'EOF' or << "EOF") -> no $VAR substitution
** If the delimiter is unquoted (<< EOF) -> each line of the body has $VAR and $? expanded
*/
int	setup_redir_heredoc(t_redirection_list *redir, t_shell_state *shell)
{
	int		fd[2];
	pid_t	pid;
	char	*delim;
	int		expand;

	expand = !(redir->target[0] == '\'' || redir->target[0] == '"');
	if (expand)
		delim = ft_strdup(redir->target);
	else
		delim = remove_quotes_str(redir->target);
	if (!delim || pipe(fd) < 0)
		return (free(delim), -1);
	pid = fork();
	if (pid < 0)
		return (free(delim), close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
		setup_heredoc_child(fd, delim, expand, shell);
	free(delim);
	close(fd[1]);
	set_parent_wait_signals();
	waitpid(pid, NULL, 0);
	set_interactive_signals();
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (close(fd[0]), -1);
	return (close(fd[0]), 0);
}
