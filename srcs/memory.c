/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:42:54 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/14 16:42:54 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
