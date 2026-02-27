/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:35 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:50:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **argv, t_shell_state *shell)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv[1])
	{
		rl_clear_history();
		exit(shell->exit_status);
	}
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		rl_clear_history();
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(argv[1]) % 256;
	rl_clear_history();
	exit(exit_code);
}

// int	ft_exit(char **argv, t_shell_state *shell)
// {
// 	ft_putstr_fd("exit\n", STDERR_FILENO);
// 	if (!argv[1])
// 		return (shell->exit_status % 256);
// 	if (!is_numeric(argv[1]))
// 	{
// 		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
// 		ft_putstr_fd(argv[1], STDERR_FILENO);
// 		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
// 		if (getpid() != getppid())  // Child process
// 			exit(255);
// 		return (255);
// 	}
// 	if (argv[2])
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
// 		return (1);
// 	}
// 	rl_clear_history();
// 	exit(ft_atoi(argv[1]) % 256);
// }
