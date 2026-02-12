/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:49:17 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/12 14:13:05 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int	valid_var_char(char c)
{
	if (ft_isalnum(c) && c == '_')
		return (1);
	return (0);
}

char	*find_var(char *str)
{
	int	c;
	
}

int	expand_envs(t_command_list *command)
{
	t_argument_list	*next;
	char			*var;

	next = command->args;
	while (next)
	{
		var = find_next_var(next->string);
		while (var)
		{
			if (is_env(var))
				expand_var();
			var = find_next_var(var + 1);
		}
}
}