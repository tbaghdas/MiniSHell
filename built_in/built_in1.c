/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:03 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/08 14:03:19 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_echo(char **str, t_shell *shell)
{
	char	*nb;

	if (str == NULL || str[0] == NULL || str[0][0] == '\0' && str[1] == NULL
		|| str[0][0] == '-' && str[0][1] == 'n'
		&& str[0][2] == '\0' && str[1] == NULL)
		return (write(1, "\n", 1), 0);
	while (*str)
	{
		if (ft_strcmp(*str, "$?") == 0)
		{
			nb = ft_itoa(shell->exit_code);
			write(1, nb, ft_strlen(nb));
			free(nb);
			str++;
			continue ;
		}
		write(1, *str, ft_strlen(*str));
		str++;
		if (*str != NULL)
			write(1, " ", 1);
	}
	return (shell->exit_code = 0, write(1, "\n", 1), 0);
}

int	built_in_cd(char **path, t_shell *shell)
{
	char	*old_wd;
	char	*new_path;

	if (path != NULL && path[0] != NULL && path[1] != NULL)
		return (shell->exit_code = 1,
			write(2, "cd: too many arguments\n", 23), 1);
	if (path == NULL || ft_strcmp(*path, "") == 0 || (*path)[0] == '~'
		|| ft_strcmp(*path, "--") == 0)
	{
		new_path = ft_getenv("HOME", shell->env);
		if (new_path == NULL)
			return (shell->exit_code = 1,
				write(2, "cd: HOME not set\n", 17), 1);
		if ((*path)[0] == '~' && (*path)[1] != '\0')
			new_path = ft_strjoin(new_path, &(*path)[1]);
	}
	else if (ft_strcmp((*path), "-") == 0)
		new_path = ft_getenv("OLDPWD", shell->env);
	else
		new_path = *path;
	old_wd = getcwd(NULL, 0);
	if (chdir(new_path) != 0)
		return (shell->exit_code = 1, perror("chdir failed"), 1);
	ft_setenv("OLDPWD", shell->env, old_wd, shell);
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
	if (str == NULL || str[0] == NULL)
	{
		if (print_env(sort_env(shell->env, 1)) != 0)
		{
			return (shell->exit_code = 1, 1);
		}
		else
		{
			return (shell->exit_code = 0, 0);
		}
	}
	if (check_for_export(str, shell->env, shell) != 0)
	{
		return (shell->exit_code = 1, 1);
	}
	return (shell->exit_code = 0, 0);
}

int	built_in_unset(char **keys, t_shell *shell)
{
	if (keys == NULL || *keys == NULL || shell->env == NULL)
	{
		return (shell->exit_code = 1, 1);
	}
	while (*keys)
	{
		del_env(shell->env, *keys);
		keys++;
	}
	return (shell->exit_code = 0, 0);
}
