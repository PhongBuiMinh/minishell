/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:08:40 by bpetrovi          #+#    #+#             */
/*   Updated: 2025/10/29 00:00:31 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		printf("%s\n", line);
		free(line);
	}
	free(line);
	return (0);
}
