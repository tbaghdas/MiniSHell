/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:44:44 by ilya              #+#    #+#             */
/*   Updated: 2025/12/08 00:27:04 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_errorer_redirs(char *line, t_shell *sh)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("'\n", 2);
	sh->exit_code = 2; //TODO?
}

void	fatal_error(char *line, t_shell *sh)
{
	int	saved;

	saved = errno;
	free_front_end_shell(sh);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(saved), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

static char	*qstate_to_str(t_qstate t)
{
	if (t == SINGLE)
		return ("'");
	if (t == DOUBLE)
		return ("\"");
	return ("UNKNOWN");
}

void	syntax_errorer_quotes(t_qstate qs, t_shell *sh)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putstr_fd(qstate_to_str(qs), 2);
	ft_putstr_fd("'\n", 2);
	sh->exit_code = 2; //TODO?
}