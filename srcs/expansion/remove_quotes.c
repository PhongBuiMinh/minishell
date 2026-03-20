/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:20:41 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/20 13:58:42 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_quotes_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_argument_quotes(t_command_list *command)
{
	t_argument_list	*argument;
	char			*new_str;

	argument = command->args;
	while (argument)
	{
		new_str = remove_quotes_str(argument->string);
		if (new_str)
		{
			free(argument->string);
			argument->string = new_str;
		}
		argument = argument->next;
	}
}

void	remove_redirection_quotes(t_command_list *command)
{
	t_redirection_list	*redir;
	char				*new_str;

	redir = command->redirs;
	while (redir)
	{
		new_str = remove_quotes_str(redir->target);
		if (new_str)
		{
			free(redir->target);
			redir->target = new_str;
		}
		redir = redir->next;
	}
}

void	remove_quotes(t_command_list *command)
{
	t_command_list	*current;

	current = command;
	while (current)
	{
		remove_argument_quotes(current);
		remove_redirection_quotes(current);
		current = current->next;
	}
}
