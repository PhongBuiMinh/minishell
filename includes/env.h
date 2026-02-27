/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:42:20 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/02/27 20:25:46 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*full_var;
	struct s_env	*next;
}	t_env;

/* env utils */
t_env	*find_env(t_env *env, char *name);
t_env	*find_env_var(t_env *env, char *name);
void	update_env(t_env **env_list, char *name, char *value);
void	add_env_var(t_env **env_list, char *name, char *value);
void	free_env_var(t_env *var);
char	**env_to_array(t_env *env);

#endif