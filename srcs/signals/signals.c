/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:38:03 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/14 22:54:00 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE

#include "minishell.h"
#include <errno.h>

volatile sig_atomic_t	g_signal_received = 0;

static void	sigint_handler(int sig)
{
	int	saved_errno;

	saved_errno = errno;
	g_signal_received = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	errno = saved_errno;
}

void	set_signal_action(int signo, void (*handler)(int))
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(signo, &sa, NULL);
}

void	set_interactive_signals(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != -1)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	set_signal_action(SIGINT, sigint_handler);
	set_signal_action(SIGQUIT, SIG_IGN);
}
