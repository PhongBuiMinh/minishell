/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:11:20 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/01 01:27:36 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	ft_memcpy(new_str + i + value_len, old_str + i + var_len,
		old_len - remove_len - i);
	new_str[new_len] = '\0';
	return (new_str);
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

int	env_cmp(char *env, char *var, int var_len)
{
	int	i;

	i = 0;
	if (!env || !var || var_len < 0)
		return (1);
	while (env[i] && var[i] && i < var_len && env[i] == var[i])
		i++;
	if (i == var_len && env[i] == '\0')
		return (0);
	return (1);
}
