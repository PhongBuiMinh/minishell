/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:49:17 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/22 02:39:10 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

void	init_env_list(t_shell_state *shell, char **envp)
{
	int		i;
	char	*eq_pos;
	char	*name;
	char	*value;

	i = 0;
	shell->env = NULL;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			name = ft_strndup(envp[i], eq_pos - envp[i]);
			value = ft_strdup(eq_pos + 1);
			add_env_var(&shell->env, name, value);
			free(name);
		}
		i++;
	}
}

void	init_shell(t_shell_state *shell, char **envp)
{
	shell->env = NULL;
	shell->exit_status = 0;
	init_env_list(shell, envp);
}

int	is_single_quoted(t_argument_list *arg)
{
	return (arg->string[0] == '\'');
}

int	is_double_quoted(t_argument_list *arg)
{
	return (arg->string[0] == '"');
}

void	replace_argument_string(t_argument_list *arg, char *new_str)
{
	char	*old_str;

	old_str = arg->string;
	arg->string = new_str;
	free(old_str);
}

void	insert_argument_strings(t_argument_list *arg, char **split, int *error)
{
	t_argument_list	*new_node;
	t_argument_list	*current;
	int				j;
	
	j = 1;
	arg->string = ft_strdup(split[0]);
	if (!arg->string)
		return ;
	current = arg;
	while (split[j])
	{
		new_node = create_arg_node(error);
		if (*error)
			return ;
		new_node->string = ft_strdup(split[j]);
		if (!new_node->string)
			return ;
		new_node->next = current->next;
		current->next = new_node;
		new_node = current;
		j++;
	}
}

void	split_argument_string(t_argument_list *arg, char *new_str, int *error)
{
	char	**split;
	char	*old_str;
	int		j;

	split = ft_split(new_str, ' ');
	if (!split)
		return ;
	old_str = arg->string;
	free(new_str);
	insert_argument_strings(arg, split, error);
	free(old_str);
	j = 0;
	while (split[j])
		free(split[j++]);
	free(split);
}

t_env	*find_env(t_env *env, char *name, int len)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	is_allowed(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int	find_len(char *str)
{
	int	i;
	int	brackets;

	i = 0;
	brackets = 0;
	if (str[i] == '{')
	{
		brackets = 1;
		i++;
	}
	while (str[i] && is_allowed(str[i]))
	{
		if (i == 0 && !ft_isalpha(str[i]))
			return (0);
		i++;
	}
	if (brackets && str[i] != '}')
		return (-1);	
	return (i);
}

void	var_not_found(t_argument_list *arg, int var_len, int i, int *remove_arg)
{
	char	*new_str;
	char	*old_str;
	int		new_len;

	old_str = arg->string;
	new_len = ft_strlen(old_str) - (var_len + 1);
	if (new_len == 0)
	{
		*remove_arg = 1;
		return ;
	}
	new_str = malloc(new_len + 1);
	if (!new_str)
		return ;
	ft_memcpy(new_str, old_str, i);
	ft_memcpy(new_str + i, old_str + var_len + i + 1, ft_strlen(old_str) - var_len - 1);
	new_str[new_len] = '\0';
	free(arg->string);
	arg->string = new_str;
}

char	*create_new_str(char *old_str, t_env *var, int i, int var_len)
{
	int		remove_len;
	int		old_len;
	int		value_len;
	int		new_len;
	char	*new_str;

	remove_len = var_len + 1;
	old_len = ft_strlen(old_str);
	value_len = ft_strlen(var->value);
	new_len = old_len - remove_len + value_len + 1;
	new_str = malloc(new_len);	
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, old_str, i);
	ft_memcpy(new_str + i, var->value, value_len);
	ft_memcpy(new_str + i + value_len, old_str + i + var_len, old_len - remove_len - i);
	new_str[new_len] = '\0';
	return (new_str);
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

void	replace_var(t_argument_list *arg, t_env *env, int i, int *remove_arg)
{
	int		var_len;
	char	*str;
	t_env	*var;

	var = NULL;
	str = arg->string;
	var_len = find_len(str + i + 1);
	if (var_len < 0)
		return ;
	else if (var_len > 0)
		var = find_env(env, str + i + 1, var_len);
	if (var)
		expand_str(arg, var, i, var_len);
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

void	expand_envs(t_command_list *command, t_env *env)
{
	t_argument_list	*current;
	t_argument_list	*next_node;
	t_argument_list	*prev;
	int				remove_arg;

	prev = NULL;
	current = command->args;
	while (current)
	{
		remove_arg = 0;
		next_node = current->next;
		find_and_expand(current, env, &remove_arg);
		if (remove_arg)
			{
				if (prev)
					prev->next = next_node;
				else
					command->args = next_node;
				free(current->string);
				free(current);
			}
		else
			prev = current;
		current = next_node;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char				*input = "Hello whats up is $this parser frfr";
	t_shell_state		shell;
	t_command_list		*first_command = NULL;
	t_command_list		*commands;
	t_argument_list		*temp_arg;
	t_redirection_list	*temp_redir;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	if (parser(input, &first_command) == -1)
		return (printf("Parser failed"), -1);
	expand_envs(first_command, shell.env);
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