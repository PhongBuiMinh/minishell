/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:49:17 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/08 20:14:24 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	valid_var_char(char c)
{
	if (ft_isalnum(c) && c == '_')
		return (1);
	return (0);
}

check_var()

char	*find_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (str + i);
		i++;
	}
	return (NULL);
}

int	expand_envs(t_command_list *command)
{
	t_argument_list	*next;
	char			*dollar_sign;

	next = command->args;
	while (next)
	{
		dollar_sign = find_var(next->string);
		if (dollar_sign)
			check_var(dollar_sign);
		next = next->next;	
	}
}