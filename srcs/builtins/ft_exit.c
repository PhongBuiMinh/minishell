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

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv[1])
		clean_exit(shell, argv, shell->exit_status);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
		clean_exit(shell, argv, 2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(argv[1]) % 256;
	clean_exit(shell, argv, exit_code);
	return (0);
}
