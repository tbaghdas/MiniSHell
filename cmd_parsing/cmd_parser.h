/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:06:05 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/17 15:44:15 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PARSER_H
# define CMD_PARSER_H

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_shell	t_shell;

// functions in cmd_parsing/cmd_parsing1.c
int		run_external_or_builtin_in_child(t_cmd *cmd, t_shell *shell);
void	closing_fds(int pipefd[2], int *prev_fd, t_cmd *has_next);
int		this_while_body(int *prev_fd, t_cmd *cur, t_shell *shell, pid_t *last);
int		execute_pipeline(t_cmd *start, t_shell *shell);

// functions in cmd_parsing/cmd_parsing2.c
int		cmd_parser(t_shell *shell);
int		is_builtin(char *cmd_name);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
char	*find_command_in_path(char *cmd_name, t_env *env);
int		handle_open_redir(t_redir *r);

// functions in cmd_parsing/cmd_parsing3.c
void	close_fds(int in_fd, int out_fd);
int		iterate_redirs_and_open(t_redir *r, int *in_fd, int *out_fd);
int		apply_final_dups(int in_fd, int out_fd);
int		apply_redirs(t_cmd *cmd);
void	free_split(char **paths);

// functions in cmd_parsing/cmd_parsing4.c
void	my_execve(char *path, char **argv, char **envp, t_shell *shell);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);

// functions in cmd_parsing/create_env.c
int		init_env(t_shell *shell, char **envp);
void	init_node_fields(t_env *node, char *env_str, char *equal_sign);
void	add_node_to_env_list(t_shell *shell, t_env *new_node);
void	free_env(t_shell *shell);

#endif