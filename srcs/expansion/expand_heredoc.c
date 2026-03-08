/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/08 03:07:36 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_hd_exit(char **str, int i, int exit_status)
{
	char	*value;
	char	*new;
	int		len;

	value = ft_itoa(exit_status);
	if (!value)
		return (-1);
	len = ft_strlen(value);
	new = create_new_str(*str, value, i, 1);
	free(value);
	if (!new)
		return (-1);
	free(*str);
	*str = new;
	return (len);
}

int	expand_hd_var(char **str, int i, t_env *env, int exit_status)
{
	int		brackets;
	int		var_len;
	t_env	*found;
	char	*new;

	if ((*str)[i + 1] == '?')
		return (expand_hd_exit(str, i, exit_status));
	brackets = 0;
	var_len = find_len(*str + i + 1, &brackets);
	if (var_len <= 0)
		return (-1);
	found = find_env(env, *str + i + 1, var_len, brackets);
	if (found)
		new = create_new_str(*str, found->value, i, var_len);
	else
		new = create_new_str(*str, "", i, var_len);
	if (!new)
		return (-1);
	free(*str);
	*str = new;
	if (found)
		return ((int)ft_strlen(found->value));
	return (0);
}

char	*expand_hd_line(char *str, t_env *env, int exit_status)
{
	int	i;
	int	val_len;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '$' || !str[i + 1])
		{
			i++;
			continue ;
		}
		val_len = expand_hd_var(&str, i, env, exit_status);
		if (val_len >= 0)
			i += val_len;
		else
			i++;
	}
	return (str);
}
