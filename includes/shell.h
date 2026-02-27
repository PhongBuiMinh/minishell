/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 20:03:02 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 20:38:55 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "env.h"

typedef struct s_shell_state
{
	t_env	*env;
	int		exit_status;
}			t_shell_state;

/* shell lifecycle */
void		init_shell(t_shell_state *shell, char **envp);

/* input helpers */
char		*join_lines(char *old, char *new);
char		*ft_strjoin_free(char *s1, char *s2);
int			check_unclosed_quotes(const char *str);

#endif