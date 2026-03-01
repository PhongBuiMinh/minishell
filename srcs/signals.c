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
	else if (g_signal_received == SIGQUIT)
		g_signal_received = 0;
	return (0);
}

static void	sigint_handler(int sig)
{
	g_signal_received = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	/* only manipulate readline when we're actually reading a line */
	if (RL_ISSTATE(RL_STATE_READCMD))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigquit_handler(int sig)
{
	(void)sig;
}

void	init_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = sigquit_handler;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
