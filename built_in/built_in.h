/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:13:00 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/09 19:39:57 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_shell	t_shell;

// functions in built_in/built_in1.c
int		built_in_echo(char **str, t_shell *shell);
int		built_in_cd(char **path, t_shell *shell);
int		built_in_pwd(t_shell *shell);
int		built_in_unset(char **key, t_shell *shell);
int		built_in_export(char **str, t_shell *shell);

// functions in built_in/built_in2.c
int		built_in_env(char **args, t_shell *shell);
int		built_in_exit(char **args, t_shell *shell);

// functions in built_in/utils.c
char	*ft_getenv(char *key, t_env *env);
void	ft_setenv(char *key, int ex_flag, char *value, t_shell *shell);
void	add_env(int ex_flag, char *key, char *value, t_shell *shell);
char	**get_env_array(t_env *env, int export_flag);
int		del_env(t_env **env, char *key);

// functions in built_in/utils2.c
int		print_env(char **env, int export);
int		array_size(char **arr);
char	**sort_env(t_env *env, int export_flag);
int		check_for_export(char **str, t_shell *shell);
int		check_export_arg(char *str);

// functions in built_in/utils3.c
void	print_export_err(char *str);
void	free_export_key_value(char *key, char *value);
int		isdigit_str(char *str);
void	free_all(t_shell *shell, char **env);
int		list_size(t_env *env);

// functions in built_in/utils4.c
void	print_cd_err(char *path);
void	print_execve_err(char *cmd_path);
void	print_cmd_not_found(char *cmd_name);
void	print_export_style(char *str);
void	setting_line(char **line, t_env *current);

#endif