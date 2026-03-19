/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/09 18:11:00 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_lines(int fd, char *delim, int expand, t_shell_state *shell)
{
	char	*line;
	size_t	len;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("> ", STDERR_FILENO);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			return (0);
		}
		if (expand)
			line = expand_hd_line(line, shell->env, shell->exit_status);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	write_heredoc_to_file(t_redirection_list *redir, t_shell_state *shell)
{
	int		fd;
	int		expand;
	char	*delim;
	int		eof;

	fd = open(redir->temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("minishell: heredoc file"), -1);
	if (ft_strchr(redir->target, '\'') || ft_strchr(redir->target, '\"'))
		expand = 0;
	else
		expand = 1;
	if (expand)
		delim = ft_strdup(redir->target);
	else
		delim = remove_quotes_str(redir->target);
	if (!delim)
		return (close(fd), -1);
	eof = process_heredoc_lines(fd, delim, expand, shell);
	if (eof)
		print_eof_warning(delim);
	free(delim);
	close(fd);
	return (0);
}

static int	run_collection_loop(t_command_list *cmds, t_shell_state *shell)
{
	t_command_list		*cmd_node;
	t_redirection_list	*redir;

	set_child_signals();
	cmd_node = cmds;
	while (cmd_node)
	{
		redir = cmd_node->redirs;
		while (redir)
		{
			if (redir->redir_type == REDIR_HEREDOC && redir->temp_file)
			{
				if (write_heredoc_to_file(redir, shell) < 0)
					exit(1);
			}
			redir = redir->next;
		}
		cmd_node = cmd_node->next;
	}
	exit(0);
}

int	collect_heredocs(t_command_list *cmds, t_shell_state *shell)
{
	pid_t	pid;
	int		status;

	assign_heredoc_filenames(cmds);
	set_parent_wait_signals();
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
		run_collection_loop(cmds, shell);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		return (unlink_heredocs(cmds), 130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink_heredocs(cmds);
		return (WEXITSTATUS(status));
	}
	return (0);
}
