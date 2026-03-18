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

char	*ft_get_next_line(int fd)
{
	char	*line;
	char	c;
	int		i;
	int		res;

	i = 0;
	line = malloc(1000);
	if (!line)
		return (NULL);
	while ((res = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		line[i++] = c;
		if (i >= 999)
			break;
	}
	if (res < 0)
		return (free(line), NULL);
	if (res == 0 && i == 0)
		return (free(line), NULL);
	line[i] = '\0';
	return (line);
}

int	check_unclosed_quotes(const char *str)
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

void increment_shlvl(t_env **env_list)
{
	t_env	*node;
	int		lvl;
	char	*tmp;

	node = find_env_var(*env_list, "SHLVL");
	if (node && node->value)
	{
		lvl = ft_atoi(node->value);
		if (lvl < 0)
			lvl = 0;
		else
			lvl++;
		tmp = ft_itoa(lvl);
		update_env_value(node, tmp);
		free(tmp);
	}
	else
		add_env_var(env_list, "SHLVL", "1");
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
	while (envp && envp[i])
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
	increment_shlvl(&shell->env);
}
