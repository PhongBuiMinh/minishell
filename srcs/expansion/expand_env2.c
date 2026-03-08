/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:35:48 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 02:37:28 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	var_not_found(t_shell_info *shell, t_argument_list *arg,
			int var_len, int i)
{
	char	*new_str;
	char	*old_str;
	int		old_len;
	int		new_len;

	old_str = arg->string;
	old_len = ft_strlen(old_str);
	new_len = old_len - (var_len + 1);
	if (new_len <= 0)
	{
		shell->remove_arg = 1;
		return ;
	}
	new_str = malloc(new_len + 1);
	if (!new_str)
		return ;
	ft_memcpy(new_str, old_str, i);
	ft_memcpy(new_str + i, old_str + var_len + i + 1,
		old_len - i - var_len - 1);
	new_str[new_len] = '\0';
	free(arg->string);
	arg->string = new_str;
}

void	expand_str(t_argument_list *arg, char *var_value, int i, int var_len)
{
	char			*new_str;
	int				error;

	error = 0;
	if (is_single_quoted(arg))
		return ;
	new_str = create_new_str(arg->string, var_value, i, var_len);
	if (!new_str)
		return ;
	if (is_double_quoted(arg) || !var_value[0])
		replace_argument_string(arg, new_str);
	else
		split_argument_string(arg, new_str, &error);
}
