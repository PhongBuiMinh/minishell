/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 19:13:26 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	read_process_line(t_shell_state *shell, char **full_input)
{
	char	*line;
	int		quote_state;

	if (*full_input)
		line = readline("> ");
	else
		line = readline("minishell$ ");
	if (!line)
	{
		if (*full_input)
			ft_putstr_fd("minishell: unclosed quote\n", STDERR_FILENO);
		printf("exit\n");
		free(*full_input);
		return (-1);
	}
	*full_input = join_lines(*full_input, line);
	free(line);
	if (!*full_input)
		return (0);
	quote_state = check_unclosed_quotes(*full_input);
	if (quote_state != 0)
		return (0);
	if (**full_input != '\0')
		add_history(*full_input);
	return (1);
}

int	process_cmd_line(t_shell_state *shell, char *full_input)
{
	t_command_list	*commands;
	int				result;

	commands = NULL;
	if (parser(full_input, &commands) == 0 && commands != NULL)
		result = execute_pipeline(commands, shell);
	else
		shell->exit_status = 2;
	free(full_input);
	return (shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_state	shell;
	char			*full_input;
	int				input_status;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	init_shell(&shell, envp);
	init_signal_handlers();
	shell.exit_status = 0;
	full_input = NULL;
	while (1)
	{
		process_signal(&shell, &full_input);
		input_status = read_process_line(&shell, &full_input);
		if (input_status < 0)
			break ;
		if (input_status == 0)
			continue ;
		shell.exit_status = process_cmd_line(&shell, full_input);
		full_input = NULL;
	}
	return (shell.exit_status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell_state	shell;
// 	char			*line;
// 	char			*complete_line;
// 	t_command_list	*commands;

// 	(void)argc;
// 	(void)argv;
// 	rl_catch_signals = 0;
// 	init_shell(&shell, envp);
// 	init_signal_handlers();
// 	shell.exit_status = 0;
// 	while (1)
// 	{
// 		if (g_signal_received == SIGINT)
// 		{
// 			shell.exit_status = 130;
// 			g_signal_received = 0;
// 		}
// 		else if (g_signal_received == SIGQUIT)
// 			g_signal_received = 0;
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*line != '\0')
// 			add_history(line);
// 		commands = NULL;
// 		if (parser(line, &commands) == 0 && commands != NULL)
// 		{
// 			shell.exit_status = execute_pipeline(commands, &shell);
// 			// free_commands(commands)
// 		}
// 		free(line);
// 	}
// 	// cleanup_shell(&shell);
// 	return (shell.exit_status);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell_state	shell;
// 	char			*line;
// 	char			*full_input;
// 	t_command_list	*commands;
// 	int				quote_state;

// 	(void)argc;
// 	(void)argv;
// 	rl_catch_signals = 0;
// 	init_shell(&shell, envp);
// 	init_signal_handlers();
// 	shell.exit_status = 0;
// 	full_input = NULL;
// 	while (1)
// 	{
// 		if (g_signal_received == SIGINT)
// 		{
// 			shell.exit_status = 130;
// 			g_signal_received = 0;
// 			free(full_input);
// 			full_input = NULL;
// 		}
// 		else if (g_signal_received == SIGQUIT)
// 			g_signal_received = 0;
// 		line = readline(full_input ? "> " : "minishell$ ");
// 		if (!line)
// 		{
// 			if (full_input)
// 				ft_putstr_fd("minishell: syntax error: unclosed quote\n", STDERR_FILENO);
// 			printf("exit\n");
// 			free(full_input);
// 			break ;
// 		}
// 		full_input = join_lines(full_input, line);
// 		free(line);
// 		if (!full_input)
// 			continue;
// 		quote_state = check_unclosed_quotes(full_input);
// 		if (quote_state != 0)
// 			continue ;
// 		if (*full_input != '\0')
// 			add_history(full_input);
// 		commands = NULL;
// 		if (parser(full_input, &commands) == 0 && commands != NULL)
// 		{
// 			shell.exit_status = execute_pipeline(commands, &shell);
// 			// free_commands(commands);
// 		}
// 		else
// 			shell.exit_status = 2;
// 		free(full_input);
// 		full_input = NULL;
// 	}
// 	// cleanup_shell(&shell);
// 	return (shell.exit_status);
// }
