/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:07:36 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/02 02:05:40 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env(t_env *env, char *name, int name_len, int brackets)
{
	while (env)
	{
		if (brackets)
		{
			if (env_cmp(env->name, name + 1, name_len - 2) == 0)
				return (env);
		}
		else if (env_cmp(env->name, name, name_len) == 0)
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
