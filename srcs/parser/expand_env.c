/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:49:17 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/01 17:45:53 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	var_not_found(t_argument_list *arg, int var_len, int i, int *remove_arg)
{
	char	*new_str;
	char	*old_str;
	int		new_len;

	old_str = arg->string;
	new_len = ft_strlen(old_str) - (var_len + 1);
	if (new_len <= 0)
	{
		*remove_arg = 1;
		return ;
	}
	new_str = malloc(new_len + 1);
	if (!new_str)
		return ;
	ft_memcpy(new_str, old_str, i);
	ft_memcpy(new_str + i, old_str + var_len + i + 1,
		ft_strlen(old_str) - var_len - 1);
	new_str[new_len] = '\0';
	free(arg->string);
	arg->string = new_str;
}

void	expand_str(t_argument_list *arg, t_env *var, int i, int var_len)
{
	char			*new_str;
	int				error;

	error = 0;
	if (is_single_quoted(arg))
		return ;
	new_str = create_new_str(arg->string, var, i, var_len);
	if (!new_str)
		return ;
	if (is_double_quoted(arg))
		replace_argument_string(arg, new_str);
	split_argument_string(arg, new_str, &error);
}

void	replace_var(t_argument_list *arg, t_env *env_list,
		int i, int *remove_arg)
{
	int		var_len;
	char	*str;
	t_env	*env;

	env = NULL;
	str = arg->string;
	var_len = find_len(str + i + 1);
	if (var_len < 0)
		return ;
	else if (var_len > 0)
		env = find_env(env_list, str + i + 1, var_len);
	if (env)
		expand_str(arg, env, i, var_len);
	else
		var_not_found(arg, var_len, i, remove_arg);
}

void	find_and_expand(t_argument_list *arg, t_env *env, int *remove_arg)
{
	int		i;
	int		dollar;
	char	*str;

	i = 0;
	str = arg->string;
	while (1)
	{
		i = 0;
		dollar = 0;
		while (str[i])
		{
			if (str[i] == '$')
			{
				dollar = 1;
				replace_var(arg, env, i, remove_arg);
				if (remove_arg)
					return ;
				break ;
			}
			i++;
		}
		if (!dollar)
			break ;
	}
}

void	expand_args(t_command_list *command,
		t_argument_list *arg, t_env *env)
{
	t_argument_list	*next;
	t_argument_list	*prev;
	int				remove_arg;

	prev = NULL;
	while (arg)
	{
		remove_arg = 0;
		next = arg->next;
		find_and_expand(arg, env, &remove_arg);
		if (remove_arg)
		{
			if (prev)
				prev->next = next;
			else
				command->args = next;
			free(arg->string);
			free(arg);
		}
		else
			prev = arg;
		arg = next;
	}
}

void	expand_envs(t_command_list *command, t_env *env)
{
	t_command_list	*current;
	t_argument_list	*arg;

	if (!command)
		return ;
	current = command;
	while (current)
	{
		arg = current->args;
		expand_args(current, arg, env);
		current = current->next;
	}
}

//int	main(int argc, char **argv, char **envp)
//{
//	char				*input = "Hello whats up is $namee parser frfr | ${whats}";
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
