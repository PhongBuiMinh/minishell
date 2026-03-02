/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:44:45 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/02 00:57:04 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "parser.h"
# include "env.h"

int		is_allowed(char c);
int		is_single_quoted(t_argument_list *arg);
int		is_double_quoted(t_argument_list *arg);
int		find_len(char *str, int *brackets);
t_env	*find_env(t_env *env, char *name, int i, int brackets);
void	replace_argument_string(t_argument_list *arg, char *new_str);
void	split_argument_string(t_argument_list *arg,
			char *new_str, int *error);
char	*create_new_str(char *old_str, t_env *var,
			int i, int var_len);
void	expand_envs(t_command_list *command, t_env *env);

#endif