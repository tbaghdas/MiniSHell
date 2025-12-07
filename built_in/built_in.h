/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:13:00 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/07 19:28:08 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

//# include "../minishell.h"
typedef struct s_env	t_env;

int		built_in_echo(char **str, t_shell *shell);
int		built_in_cd(char **path, t_shell *shell);
int		built_in_pwd(t_shell *shell);
int		built_in_unset(char **key, t_shell *shell);
int		built_in_export(char **str, t_shell *shell);

int		built_in_env(char **args, t_shell *shell);
int		built_in_exit(char **args, t_shell *shell);

char	*ft_getenv(char *key, t_env *env);
void	ft_setenv(char *key, t_env *env, char *value);
void	add_env(t_env **env, char *key, char *value);
char	**get_env_array(t_env *env);
int		del_env(t_env **env, char *key);

int		print_env(char **env);
int		array_size(char **arr);
char	**sort_env(t_env *env);
int		check_for_export(char **str, t_env *env);
int		check_export_arg(char *str);

void	print_export_err(char *str);
void	free_export_key_value(char *key, char *value);
int		isdigit_str(char *str);

#endif