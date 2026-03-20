/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:02:25 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/03/20 01:25:30 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ambiguous_redirect(t_argument_list *arg)
{
	if (!arg || !arg->string || arg->next != NULL)
		return (1);
	return (0);
}

static int	process_redir(t_shell_info *shell,
	t_command_list *fake_cmd,
	t_argument_list *fake_arg,
	t_redirection_list *redir)
{
	char	*old;

	old = redir->target;
	fake_arg->string = ft_strdup(old);
	if (!fake_arg->string)
		return (-1);
	expand_args(shell, fake_cmd, fake_arg);
	if (is_ambiguous_redirect(fake_arg))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(old, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		return (-1);
	}
	free(old);
	redir->target = fake_arg->string;
	fake_arg->string = NULL;
	return (0);
}

int	expand_redirs(t_shell_info *shell, t_command_list *command)
{
	t_command_list		*fake_cmd;
	t_argument_list		*fake_arg;
	t_redirection_list	*cur;

	shell->remove_arg = 0;
	cur = command->redirs;
	fake_cmd = malloc(sizeof(t_command_list));
	if (!fake_cmd)
		return (-1);
	init_command(fake_cmd);
	fake_arg = create_arg_node(0);
	if (!fake_arg)
		return (free(fake_cmd), -1);
	fake_cmd->args = fake_arg;
	while (cur)
	{
		if (process_redir(shell, fake_cmd, fake_arg, cur) == -1)
			return (free_all(fake_cmd), -1);
		cur = cur->next;
	}
	return (free(fake_arg), free(fake_cmd), 0);
}
