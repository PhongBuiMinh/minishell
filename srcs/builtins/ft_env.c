/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 18:50:31 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_env(t_shell_state *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		ft_putendl_fd(curr->full_var, STDOUT_FILENO);
		curr = curr->next;
	}
	return (0);
}
