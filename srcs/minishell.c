/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:08:40 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/28 02:44:34 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	t_command_list	*commands;
	t_command_list	*first_command = NULL;

	char	*input = "echo -mf yo |  wassup  |  echo file.txt > how its going";
	if (parser(input, &first_command) == -1)
		return (printf("Parser failed"), -1);
	commands = first_command;
	while (commands)
	{
		printf("Current command: %s\n", commands->args->string);
		printf("All arguments: \n");
		commands->args = commands->args->next;
		while (commands->args)
		{
			printf("%s\n", commands->args->string);
			commands->args = commands->args->next;
		}
		printf("All redirections: \n");
		while (commands->redirs)
		{
			printf("%i, %s\n", commands->redirs->redir_type, commands->redirs->target);
			commands->redirs = commands->redirs->next;
		}
		printf("-----------------------------------------------\n");
		commands = commands->next;
	}
	free_all(first_command);
	return (0);
}
