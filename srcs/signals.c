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

volatile sig_atomic_t	g_signal_received = 0;

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

static void	sigint_handler(int sig)
{
	g_signal_received = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
}

static void	set_signal_action(int signo, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(signo, &sa, NULL);
}

void	set_interactive_signals(void)
{
	set_signal_action(SIGINT, sigint_handler);
	set_signal_action(SIGQUIT, sigquit_handler);
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
