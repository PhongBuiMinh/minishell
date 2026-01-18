/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:44:20 by fbui-min          #+#    #+#             */
/*   Updated: 2026/01/18 21:41:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("pwd"), 1);
	printf("%s\n", cwd);
	return (0);
}
