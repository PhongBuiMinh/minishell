/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 20:40:52 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 20:40:54 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

/* dispatcher */
int		is_builtin(const char *cmd);
int		handle_builtin(char *cmd, char **argv, t_shell_state *shell);

/* builtins */
int		ft_cd(char **argv, t_shell_state *shell);
int		ft_echo(char **argv);
int		ft_env(t_shell_state *shell);
int		ft_exit(char **argv, t_shell_state *shell);
int		ft_export(char **args, t_shell_state *shell);
int		ft_pwd(void);
int		ft_unset(char **argv, t_shell_state *shell);

#endif