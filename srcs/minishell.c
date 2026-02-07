/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:08:40 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/07 21:00:43 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	t_command_list		*commands;
	t_command_list		*first_command = NULL;
	t_argument_list		*temp_arg;
	t_redirection_list	*temp_redir;

	char	*input;
	if (parser(input, &first_command) == -1)
		return (printf("Parser failed"), -1);
	commands = first_command;
	while (commands)
	{
		temp_arg = commands->args;
		temp_redir = commands->redirs;
		printf("Current command: %s\n", temp_arg->string);
		printf("All arguments: \n");
		temp_arg = temp_arg->next;
		while (temp_arg)
		{
			printf("%s\n", temp_arg->string);
			temp_arg = temp_arg->next;
		}
		printf("All redirections: \n");
		while (temp_redir)
		{
			printf("%i, %s\n", temp_redir->redir_type, temp_redir->target);
			temp_redir = temp_redir->next;
		}
		printf("-----------------------------------------------\n");
		commands = commands->next;
	}
	free_all(first_command);
	return (0);
}
