/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:03 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/09 19:47:39 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_echo(char **str, t_shell *shell)
{
	char	*nb;

	if (str == NULL || str[0] == NULL || str[1] == NULL
		|| (str[1][0] == '\0' && str[2] == NULL)
		|| (str[1][0] == '-' && str[1][1] == 'n'
		&& str[1][2] == '\0' && str[2] == NULL))
		return (write(1, "\n", 1), 0);
	while (*(++str))
	{
		if (ft_strcmp(*str, "$?") == 0)
		{
			nb = ft_itoa(shell->exit_code);
			write(1, nb, ft_strlen(nb));
			if (*(str + 1) != NULL)
				write(1, " ", 1);
			free(nb);
			continue ;
		}
		write(1, *str, ft_strlen(*str));
		if (*(str + 1) != NULL)
			write(1, " ", 1);
	}
	return (shell->exit_code = 0, write(1, "\n", 1), 0);
}

int	built_in_cd(char **path, t_shell *shell)
{
	char	*old_wd;
	char	*new_path;

	if (path && path[0] && path[1] && path[2] != NULL && path[2][0] != '\0')
		return (shell->exit_code = 1,
			write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!path || !path[0] || path[1] == NULL || ft_strcmp(path[1], "") == 0
		|| path[1][0] == '~' || ft_strcmp(path[1], "--") == 0)
	{
		new_path = ft_getenv("HOME", shell->env);
		if (new_path == NULL)
			return (shell->exit_code = 1,
				write(2, "minishell: cd: HOME not set\n", 30), 1);
		if (path[1] != NULL && path[1][0] == '~' && path[1][1] != '\0')
			new_path = ft_strjoin(new_path, &path[1][1]);
	}
	else if (ft_strcmp(path[1], "-") == 0)
		new_path = ft_getenv("OLDPWD", shell->env);
	else
		new_path = path[1];
	old_wd = getcwd(NULL, 0);
	if (chdir(new_path) != 0)
		return (shell->exit_code = 1, print_cd_err(new_path), 1);
	ft_setenv("OLDPWD", 1, old_wd, shell);
	return (shell->exit_code = 0, 0);
}

int	built_in_pwd(t_shell *shell)
{
	char	*work_dir;

	work_dir = getcwd(NULL, 0);
	if (work_dir == NULL)
	{
		return (shell->exit_code = 1, 1);
	}
	printf("%s\n", work_dir);
	free (work_dir);
	return (shell->exit_code = 0, 0);
}

int	built_in_export(char **str, t_shell *shell)
{
	if (shell == NULL || shell->env == NULL)
	{
		return (shell->exit_code = 1, 1);
	}
	if (str == NULL || str[0] == NULL || str[1] == NULL)
	{
		if (print_env(sort_env(shell->env, 1), 1) != 0)
		{
			return (shell->exit_code = 1, 1);
		}
		else
		{
			return (shell->exit_code = 0, 0);
		}
	}
	str++;
	if (check_for_export(str, shell) != 0)
	{
		return (shell->exit_code = 1, 1);
	}
	return (shell->exit_code = 0, 0);
}

int	built_in_unset(char **keys, t_shell *shell)
{
	if (keys == NULL || keys[0] == NULL
		|| keys[1] == NULL || shell->env == NULL)
	{
		return (shell->exit_code = 0, 1);
	}
	keys++;
	while (*keys)
	{
		del_env(&shell->env, *keys);
		keys++;
	}
	return (shell->exit_code = 0, 0);
}
