/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/07 01:12:36 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	// dprintf(2, "DEBUG: ft_echo START\n");
	// dprintf(2, "DEBUG: argv[0]='%s', argv[1]='%s'\n", argv[0],
		// argv[1] ? argv[1] : "NULL");
	i = 1;
	newline = 1;
	if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		newline = 0;
		i++;
	}
	// dprintf(2, "DEBUG: about to write to STDOUT\n");
	while (argv[i])
	{
		dprintf(2, "DEBUG: writing '%s'\n", argv[i]);
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
	{
		// dprintf(2, "DEBUG: writing newline\n");
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	// dprintf(2, "DEBUG: ft_echo END\n");
	return (0);
}
