/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:38:35 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 21:41:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(char **argv, t_shell_state *shell)
{
	int	exit_code;

	printf("exit\n");
	if (!argv[1])
		exit(shell->exit_status);
	if (!is_numeric(argv[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(255);
	}
	if (argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit_code = ft_atoi(argv[1]) % 256;
	exit(exit_code);
}
