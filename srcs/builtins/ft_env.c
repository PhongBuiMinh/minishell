/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_shell_state *shell)
{
	t_env	*curr;

	if (args[1] && args[1][0] == '-')
	{
		ft_putstr_fd("minishell: no option\n", STDERR_FILENO);
		return (2);
	}
	if (!args[1])
	{
		curr = shell->env;
		while (curr)
		{
			if (ft_strchr(curr->full_var, '='))
				ft_putendl_fd(curr->full_var, STDOUT_FILENO);
			curr = curr->next;
		}
		return (0);
	}
	ft_putstr_fd("minishell: env: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (127);
}
