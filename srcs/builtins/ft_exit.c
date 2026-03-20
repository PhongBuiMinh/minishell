/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:35 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/08 05:24:52 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_exit(t_shell_state *shell, char **argv, int code)
{
	rl_clear_history();
	free_env_list(shell->env);
	free(argv);
	exit(code);
}

static int	is_overflow(unsigned long long n, int digit, int sign)
{
	unsigned long long	max;

	max = 922337203685477580ULL;
	if (n > max)
		return (1);
	if (n == max)
	{
		if (sign == 1 && digit > 7)
			return (1);
		if (sign == -1 && digit > 8)
			return (1);
	}
	return (0);
}

int	advanced_atoll(char *str, long long *res)
{
	unsigned long long	n;
	int					sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (is_overflow(n, *str - '0', sign))
			return (0);
		n = n * 10 + (*str++ - '0');
	}
	if (*str != '\0')
		return (0);
	*res = (long long)(n * sign);
	return (1);
}

int	ft_exit(char **argv, t_shell_state *shell)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv[1])
		clean_exit(shell, argv, shell->exit_status);
	if (!advanced_atoll(argv[1], &exit_code))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
		clean_exit(shell, argv, 2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	clean_exit(shell, argv, exit_code);
	return (0);
}
