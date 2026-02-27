/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:45:20 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 19:47:20 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "exec.h"

extern volatile sig_atomic_t	g_signal_received;

void	init_signal_handlers(void);
void	set_child_signals(void);
int		process_signal(t_shell_state *shell, char **full_input);

#endif
