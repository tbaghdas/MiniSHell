/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:03 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/11/30 16:22:32 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	built_in_echo(char *str)
{
	int	fd;

	fd = 1;
	if (str == NULL)
	{
		return (1);
	}
	write(fd, str, ft_strlen(str));
	if (str[0] == '-' && str[1] == 'n' || str[0] == '\0')
	{
		write(fd, "\n", 1);
	}
	return (0);
}

int	built_in_cd(char *path, t_env *env)
{
	char	*old_wd;
	char	*new_path;

	if (path == NULL)
		return (1);
	if (ft_strcmp(path, "~") == 0 || ft_strcmp(path, "") == 0
		|| ft_strcmp(path, "--") == 0 || (path[0] == '~' && path[1] != '\0'))
	{
		new_path = ft_getenv("HOME", env);
		if (new_path == NULL)
			return (write(2, "cd: HOME not set\n", 17), 1);
		if (path[0] == '~' && path[1] != '\0')
			path = ft_strjoin(new_path, &path[1]);
		else
			path = new_path;
	}
	else if (ft_strcmp(path, "-") == 0)
		path = ft_getenv("OLDPWD", env);
	old_wd = getcwd();
	if (chdir(path) != 0)
		return (perror("chdir failed"), 1);
	ft_setenv("OLDPWD", env, old_wd);
	return (0);
}

int	built_in_pwd(void)
{
	char	*work_dir;

	work_dir = getcwd(NULL, 0);
	if (work_dir == NULL)
	{
		return (1);
	}
	printf("%s\n", work_dir);
	free (work_dir);
	return (0);
}

int	built_in_export(char *str, t_env *env)
{
	if (str == NULL || env == NULL)
	{
		return (1);
	}
	if (str[0] == '\0')
	{
		if (print_env(sort_env(get_env_arr(env))) != 0)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	if (check_for_export(str, env) != 0)
	{
		return (1);
	}
	return (0);
}

int	built_in_unset(char *key, t_env *env)
{
	if (key == NULL || env == NULL)
	{
		return (1);
	}
	if (del_env(env, key) == -2)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}
