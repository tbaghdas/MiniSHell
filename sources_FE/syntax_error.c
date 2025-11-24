/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:44:44 by ilya              #+#    #+#             */
/*   Updated: 2025/11/24 01:10:54 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_errorer(char *line)
{
	int saved;
	
	saved = dup(1);
	dup2(2, 1);
	printf("syntax error near unexpected token `%s'\n", line);
	dup2(saved, 1);
	close(saved);
}