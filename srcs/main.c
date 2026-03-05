/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/05 19:10:34 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_process_line(char **full_input)
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

	commands = NULL;
	if (parser(full_input, &commands) == -1)
		shell->exit_status = 2;
	free(full_input);
	if (commands != NULL)
	{
		shell->exit_status = execute_pipeline(commands, shell);
		free_all(commands);
	}
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
	set_interactive_signals();
	shell.exit_status = 0;
	full_input = NULL;
	while (1)
	{
		process_signal(&shell, &full_input);
		input_status = read_process_line(&full_input);
		if (input_status < 0)
			break ;
		if (input_status == 0)
			continue ;
		shell.exit_status = process_cmd_line(&shell, full_input);
		full_input = NULL;
	}
	free_env_list(shell.env);
	return (shell.exit_status);
}
