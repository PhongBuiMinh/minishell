/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:57:52 by fbui-min          #+#    #+#             */
/*   Updated: 2025/12/29 07:17:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// builtin_env - Display all environment variables
int builtin_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

// builtin_exit - Exit the shell with status code
int builtin_exit(char **argv, t_shell *sh)
{
	int	exit_code;

	exit_code = sh->last_status;
	printf("exit\n");
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
			exit_code = 2;
		else if (argv[2])
			return (1);
		else
			exit_code = ft_atoi(argv[1]) % 256;
	}
	cleanup_shell(sh);
	exit(exit_code);
}

// execute_builtin - Route command to appropriate builtin handler
int execute_builtin(t_cmd *cmd, t_shell *sh)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	if (ft_strncmp(cmd->argv[0], "echo", 3) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (builtin_cd(cmd->argv, sh->env));
	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
		return (builtin_export(cmd->argv, &sh->env));
	if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return (builtin_unset(cmd->argv, &sh->env));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(sh->env));
	if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
		return (builtin_exit(cmd->argv, sh));
	return (-1);
}

// is_builtin_cmd - Check if command is a builtin
int is_builtin_cmd(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0 || ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0 || ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

void cleanup_shell(t_shell *sh)
{
	t_env	*current;
	t_env	*next;

	if (!sh)
		return ;
	current = sh->env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}
