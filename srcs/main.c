/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/13 20:35:33 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_process_line(t_shell_state *shell, char **full_input)
{
	char	*line;
	int		quote_state;

	*full_input = NULL;
	if (isatty(STDIN_FILENO))
		line = readline("minishell$ ");
	else
		line = ft_get_next_line(STDIN_FILENO);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		return (-1);
	}
	if (*line == '\0')
		return (free(line), 0);
	quote_state = check_unclosed_quotes(line);
	if (quote_state != 0)
	{
		ft_putstr_fd("minishell: unclosed quote\n", STDERR_FILENO);
		shell->exit_status = 2;
		return (free(line), 0);
	}
	*full_input = line;
	return (add_history(*full_input), 1);
}

int	process_cmd_line(t_shell_state *shell, char *full_input)
{
	t_command_list	*commands;
	char			**pipelines;
	int				i;

	pipelines = ft_split(full_input, '\n');
	free(full_input);
	if (!pipelines)
		return (shell->exit_status);
	i = 0;
	while (pipelines[i])
	{
		commands = NULL;
		if (parser(pipelines[i], &commands) != -1)
		{
			if (commands)
				shell->exit_status = execute_pipeline(commands, shell);
			free_all(commands);
		}
		else
			shell->exit_status = 2;
		free(pipelines[i++]);
	}
	free(pipelines);
	return (shell->exit_status);
}

static int	shell_loop(t_shell_state *shell)
{
	char	*full_input;
	int		input_status;

	while (1)
	{
		full_input = NULL;
		if (process_signal(shell, &full_input))
			continue ;
		input_status = read_process_line(shell, &full_input);
		if (input_status < 0)
			break ;
		if (input_status == 0)
			continue ;
		if (g_signal_received == SIGINT)
		{
			shell->exit_status = 130;
			g_signal_received = 0;
		}
		shell->exit_status = process_cmd_line(shell, full_input);
	}
	free(full_input);
	return (shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_state	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	set_interactive_signals();
	shell.exit_status = 0;
	shell_loop(&shell);
	free_env_list(shell.env);
	return (shell.exit_status);
}

// Disabling bracketed paste mode
// ft_putstr_fd("\033[?2004l", STDOUT_FILENO);
// rl_variable_bind("enable-bracketed-paste", "off");

// int	process_cmd_line(t_shell_state *shell, char *full_input)
// {
// 	t_command_list	*commands;

// 	commands = NULL;
// 	if (g_signal_received == SIGINT)
// 	{
// 		shell->exit_status = 130;
// 		g_signal_received = 0;
// 	}
// 	if (parser(full_input, &commands) == -1)
// 	{
// 		free(full_input);
// 		if (commands)
// 			free_all(commands);
// 		return (2);
// 	}
// 	free(full_input);
// 	if (commands != NULL)
// 	{
// 		shell->exit_status = execute_pipeline(commands, shell);
// 		free_all(commands);
// 	}
// 	return (shell->exit_status);
// }

// char	*join_lines(char *old, char *new)
// {
// 	char	*with_newline;
// 	char	*result;

// 	if (!old)
// 		return (ft_strdup(new));
// 	with_newline = ft_strjoin(old, "\n");
// 	if (!with_newline)
// 		return (NULL);
// 	result = ft_strjoin(with_newline, new);
// 	free(with_newline);
// 	free(old);
// 	return (result);
// }

// int	read_process_line(char **full_input)
// {
// 	char	*line;
// 	int		quote_state;

// 	if (*full_input)
// 		line = readline("> ");
// 	else
// 		line = readline("minishell$ ");
// 	if (!line)
// 	{
// 		if (*full_input)
// 			ft_putstr_fd("minishell: unclosed quote\n", STDERR_FILENO);
// 		printf("exit\n");
// 		free(*full_input);
// 		return (-1);
// 	}
// 	*full_input = join_lines(*full_input, line);
// 	free(line);
// 	if (!*full_input)
// 		return (0);
// 	quote_state = check_unclosed_quotes(*full_input);
// 	if (quote_state != 0)
// 		return (0);
// 	if (**full_input != '\0')
// 		add_history(*full_input);
// 	return (1);
// }

// static int	shell_loop(t_shell_state *shell)
// {
// 	char	*full_input;
// 	int		input_status;

// 	full_input = NULL;
// 	while (1)
// 	{
// 		if (process_signal(shell, &full_input))
// 			continue ;
// 		input_status = read_process_line(&full_input);
// 		if (input_status < 0)
// 			break ;
// 		if (input_status == 0)
// 			continue ;
// 		shell->exit_status = process_cmd_line(shell, full_input);
// 		full_input = NULL;
// 	}
// 	free(full_input);
// 	return (shell->exit_status);
// }
