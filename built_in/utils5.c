/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:06:37 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/17 16:24:09 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_free(char *str)
{
	if (str != NULL)
	{
		free(str);
	}
}

int	*check_append(int ex_flag, char *str)
{
	int		*flags;
	int		flag;
	char	*plus;

	flag = 0;
	plus = ft_strchr(str, '+');
	if (plus != NULL && plus[0] != '\0' && plus[1] == '=')
		flag = 1;
	if (ex_flag && flag)
		flags = (int []){1, 1};
	else if (ex_flag && !flag)
		flags = (int []){1, 0};
	else if (!ex_flag && flag)
		flags = (int []){0, 1};
	else
		flags = (int []){0, 0};
	return (flags);
}

char	*get_delim(char *str, char *equal_sign)
{
	if (equal_sign && equal_sign > str && equal_sign[-1] == '+')
		return (equal_sign - 1);
	return (equal_sign);
}

void	change_shlvl_value(t_shell *shell)
{
	int		res;
	char	*val;

	res = 0;
	val = ft_getenv("SHLVL", shell->env);
	if (val)
		res = ft_atoi(val);
	if (res == 1000)
		res = 1;
	else
		res++;
	ft_setenv("SHLVL", (int []){1, 0}, ft_itoa(res), shell);
}
