/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:49:17 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/13 20:44:43 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

t_env	*find_env_var(t_env *env, char *name, int len)
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

char	*create_new_str(char *old_str, t_env *var, int var_len, int i)
{
	int		brackets;
	int		new_str_len;
	char	*new_str;
	int		c;

	c = 0;
	new_str_len = old_str - var_len + ft_strlen(var->value) + 1;
	new_str = malloc(new_str_len);
	if (!new_str)
		return (NULL);
	brackets = 0;
	if (old_str[i + 1] == '{')
		brackets = 1;
	while (c < new_str_len)
	{
		if (c == i)
		{
			ft_memcpy(new_str + c, var->value, ft_strlen(var->value));
			c += ft_strlen(var->value);
		}
		new_str[c] = old_str[c];
		c++;
	}
}


char	*expand_str(t_argument_list *arg, t_env *var, int i, int var_len)
{
	char	*new_str;
	char	**new_args;
	char	*temp;
	
	new_str = create_new_str();
	if (quoted)
	{
		temp = arg->string;
		arg->string = new_str;
		free(temp);
		return ;
	}
	new_args = ft_split(new_str, " ");
	free(arg->string);
	while (new_args)
	{
		arg->string = *new_args;
		*new_args++;
	}
	free(new_args);
}

int	replace_var(int i, t_argument_list *arg, t_env *env)
{
	int		var_len;
	char	*str;
	t_env	*var;

	str = arg->string;
	var_len = find_var_len(str + i + 1);
	var = find_env_var(env, str + i + 1, var_len);
	expand_str(arg, var, i, var_len);
}

char	*find_and_expand(t_argument_list *arg, t_env *env)
{
	int		i;
	t_env	*var;
	char	*str;

	i = 0;
	str = arg->string;
	while (str[i])
	{
		if (str[i] == '$')
		{
			replace_var(i, arg, env);
		}
		i++;
	}
}

int	expand_envs(t_command_list *command, t_env *env)
{
	t_argument_list	*next;

	next = command->args;
	while (next)
	{
		find_and_expand(next, env);
		next = next->next;
	}
}