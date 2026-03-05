/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:42:54 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/05 18:15:23 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	free_env_var(t_env *var)
{
	if (!var)
		return ;
	free(var->name);
	free(var->value);
	free(var->full_var);
	free(var);
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free_env_var(env);
		env = next;
	}
}
