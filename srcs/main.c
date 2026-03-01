/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
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
	if (parser(full_input, &commands) == 0 && commands != NULL)
		execute_pipeline(commands, shell);
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
		input_status = read_process_line(&full_input);
		if (input_status < 0)
			break ;
		if (input_status == 0)
			continue ;
		shell.exit_status = process_cmd_line(&shell, full_input);
		full_input = NULL;
	}
	return (shell.exit_status);
}
