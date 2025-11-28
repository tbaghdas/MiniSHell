/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 02:50:02 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/26 23:18:56 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_input_redir(t_toktyp type)
{
	return (type == REDIR_IN || type == HEREDOC);
}

int	is_output_redir(t_toktyp type)
{
	return (type == REDIR_OUT || type == REDIR_APP);
}
