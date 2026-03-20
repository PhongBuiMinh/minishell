/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:44:20 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args && args[1] && args[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: no options allowed\n", STDERR_FILENO);
		return (2);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	ft_putstr_fd("pwd: error retrieving current directory: ", STDERR_FILENO);
	ft_putstr_fd("getcwde: cannot access parent directories\n", STDERR_FILENO);
	return (1);
}
