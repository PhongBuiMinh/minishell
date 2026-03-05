/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/02/27 19:51:54 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include "minishell.h"

int	process_signal(t_shell_state *shell, char **full_input)
{
	if (g_signal_received == SIGINT)
	{
		shell->exit_status = 130;
		g_signal_received = 0;
		free(*full_input);
		*full_input = NULL;
		return (1);
	}
	return (0);
}

void	set_parent_wait_signals(void)
{
	set_signal_action(SIGINT, SIG_IGN);
	set_signal_action(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	set_signal_action(SIGINT, SIG_DFL);
	set_signal_action(SIGQUIT, SIG_DFL);
}
