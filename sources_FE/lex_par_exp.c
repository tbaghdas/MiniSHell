/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_par_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:32:24 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/17 16:18:12 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_shell *sh, char *line)
{
	t_qstate	qs;

	qs = NONE;
	if (lexer(line, sh, &qs))
		return (1);
	if (sh->tok && sh->tok->type == PIPE)
		return (syntax_errorer_redirs(sh->tok->content, sh), 1);
	if (parser(sh->tok, sh))
		return (1);
	expander(sh);
	return (0);
}
