/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpetrovi <bpetrovi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:52:32 by bpetrovi          #+#    #+#             */
/*   Updated: 2026/01/19 18:56:35 by bpetrovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

void	lexer_skip(t_lexer *lex)
{
	t_token			*tok;

	tok = lexer_advance(lex);
	free(tok);
}
