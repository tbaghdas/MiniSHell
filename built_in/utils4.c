/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:59:48 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/15 17:23:30 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_err(char *path)
{
	write(2, "minishell: cd: ", 15);
	if (path != NULL)
	{
		write(2, path, ft_strlen(path));
	}
	write(2, ": ", 2);
	perror("");
}

void	print_exe_err(char *cmd_path)
{
	write(2, "minishell: ", 11);
	if (cmd_path != NULL)
	{
		write(2, cmd_path, ft_strlen(cmd_path));
	}
	write(2, ": ", 2);
	perror("");
}

void	print_cmd_not_found(char *cmd_name)
{
	if (cmd_name != NULL)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
	}
	write(2, ": command not found\n", 20);
}

void	print_export_style(char *str)
{
	char	*equal_sign;

	ft_putstr_fd("declare -x ", 1);
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		write(1, str, equal_sign + 1 - str);
		write(1, "\"", 1);
		ft_putstr_fd(equal_sign + 1, 1);
		write(1, "\"", 1);
	}
	else
	{
		ft_putstr_fd(str, 1);
	}
}

void	setting_line(char **line, t_env *current)
{
	char	*temp;

	if (current->value != NULL)
	{
		*line = ft_strjoin(current->key, "=");
		temp = ft_strjoin(*line, current->value);
		free(*line);
		*line = temp;
	}
	else
		*line = ft_strdup(current->key);
}
