/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:44:45 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/09 17:39:38 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "parser.h"
# include "env.h"

typedef struct s_shell_info
{
	t_command_list				*command;
	t_env						*env;
	int							exit_status;
	int							bad_substitution;
	int							remove_arg;
}			t_shell_info;

int		is_allowed(char c);
int		is_double_quoted(char *str, int dollar_pos);
int		find_len(char *str, int *brackets);
char	*find_env(t_env *env, char *name, int i, int brackets);
void	replace_argument_string(t_argument_list *arg, char *new_str);
void	split_argument_string(t_argument_list *arg,
			char *new_str, int *error);
void	var_not_found(t_shell_info *shell, t_argument_list *arg,
			int var_len, int i);
void	expand_str(t_argument_list *arg, char *var_value, int i, int var_len);
char	*create_new_str(char *old_str, char *var_value,
			int i, int var_len);
char	*remove_quotes_str(char *str);
void	remove_quotes(t_command_list *command);
int		expand_envs(t_command_list *command, t_env *env, int exit_status);
char	*remove_quotes_str(char *str);
//char	*expand_hd_line(char *str, t_env *env, int exit_status);

#endif