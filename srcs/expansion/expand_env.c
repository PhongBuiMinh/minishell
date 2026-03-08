/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:49:17 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 23:49:42 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_var(t_shell_info *shell, t_argument_list *arg, int i)
{
	int		var_len;
	int		brackets;
	char	*str;
	char	*var_value;

	brackets = 0;
	var_value = NULL;
	str = arg->string;
	if (str[i + 1] == '?')
	{
		var_value = ft_itoa(shell->exit_status);
		if (!var_value)
			return ;
		return (expand_str(arg, var_value, i, 1));
	}
	var_len = find_len(str + i + 1, &brackets);
	if (var_len < 0)
		return ;
	else if (var_len > 0)
		var_value = find_env(shell->env, str + i + 1, var_len, brackets);
	if (var_value)
		expand_str(arg, var_value, i, var_len);
	else
		var_not_found(shell, arg, var_len, i);
}

static int	find_dollar(char *str, int starting_pos)
{
	int	inside_quotes;
	int	i;

	i = starting_pos;
	inside_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (inside_quotes)
				inside_quotes = 0;
			else
				inside_quotes = 1;
		}
		if (str[i] == '$' && !inside_quotes)
			return (i);
		i++;
	}
	return (-1);
}

void	find_and_expand(t_shell_info *shell, t_argument_list *arg)
{
	int	pos;

	pos = find_dollar(arg->string, 0);
	while (pos != -1)
	{
		replace_var(shell, arg, pos);
		if (shell->remove_arg)
			return ;
		pos = find_dollar(arg->string, pos);
	}
}

void	expand_args(t_shell_info *shell, t_command_list *current,
			t_argument_list *arg)
{
	t_argument_list	*next;
	t_argument_list	*prev;

	prev = NULL;
	while (arg)
	{
		shell->remove_arg = 0;
		next = arg->next;
		find_and_expand(shell, arg);
		if (shell->remove_arg)
		{
			if (prev)
				prev->next = next;
			else
				current->args = next;
			free(arg->string);
			free(arg);
		}
		else
			prev = arg;
		arg = next;
	}	
}

void	expand_envs(t_command_list *command, t_env *env, int exit_status)
{
	t_shell_info	shell;
	t_command_list	*current;
	t_argument_list	*arg;

	shell.remove_arg = 0;
	shell.exit_status = exit_status;
	shell.command = command;
	shell.env = env;
	if (!command)
		return ;
	current = command;
	while (current)
	{
		arg = current->args;
		expand_args(&shell, current, arg);
		current = current->next;
	}
	current = command;
	remove_quotes(current);
}

//int	main(int argc, char **argv, char **envp)
//{
//	char				*input = "Hello whats up is $namee 
//							parser frfr | ${whats}";
//	t_shell_state		shell;
//	t_command_list		*first_command = NULL;
//	t_command_list		*commands;
//	t_argument_list		*temp_arg;
//	t_redirection_list	*temp_redir;

//	(void)argc;
//	(void)argv;
//	init_shell(&shell, envp);
//	if (parser(input, &first_command) == -1)
//		return (printf("Parser failed"), -1);
//	expand_envs(first_command, shell.env);
//	commands = first_command;
//	while (commands)
//	{
//		temp_arg = commands->args;
//		temp_redir = commands->redirs;
//		printf("Current command: %s\n", temp_arg->string);
//		printf("All arguments: \n");
//		temp_arg = temp_arg->next;
//		while (temp_arg)
//		{
//			printf("%s\n", temp_arg->string);
//			temp_arg = temp_arg->next;
//		}
//		printf("All redirections: \n");
//		while (temp_redir)
//		{
//			printf("%i, %s\n", temp_redir->redir_type, temp_redir->target);
//			temp_redir = temp_redir->next;
//		}
//		printf("-----------------------------------------------\n");
//		commands = commands->next;
//	}
//	while (shell.env)
//	{
//		t_env *temp = shell.env;
//		shell.env = shell.env->next;
//		free(temp);
//	}
//	free_all(first_command);
//	return (0);
//}
