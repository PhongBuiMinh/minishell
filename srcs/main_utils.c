/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:44:54 by fbui-min          #+#    #+#             */
/*   Updated: 2026/03/01 01:08:49 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_unclosed_quotes(const char *str)
{
	int	single;
	int	double_q;
	int	i;

	single = 0;
	double_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single = !single;
		else if (str[i] == '"' && !single)
			double_q = !double_q;
		i++;
	}
	if (single)
		return (1);
	if (double_q)
		return (2);
	return (0);
}

char *join_lines(char *old, char *new)
{
	char *with_newline;
	char *result;

	if (!old)
		return (ft_strdup(new));
	with_newline = ft_strjoin(old, "\n");
	if (!with_newline)
		return (NULL);
	result = ft_strjoin(with_newline, new);
	free(with_newline);
	free(old);
	return (result);
}

void	init_shell(t_shell_state *shell, char **envp)
{
	int		i;
	char	*eq_pos;
	char	*name;
	char	*value;

	i = 0;
	shell->env = NULL;
	shell->exit_status = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			name = ft_strndup(envp[i], eq_pos - envp[i]);
			value = ft_strdup(eq_pos + 1);
			if (name && value)
				add_env_var(&shell->env, name, value);
			free(name);
			free(value);
		}
		i++;
	}
}
