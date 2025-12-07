/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:06:05 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/07 19:22:13 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PARSER_H
# define CMD_PARSER_H

int		run_external_or_builtin_in_child(t_cmd *cmd, t_shell *shell);
void	the_child_process(int pipefd[2], int prev_fd,
			t_cmd *cur, t_shell *shell);
void	closing_fds(int pipefd[2], int *prev_fd, t_cmd *has_next);
void	this_while_body(int *prev_fd, t_cmd *cur, t_shell *shell);
int		execute_pipeline(t_cmd *start, t_shell *shell);

int		cmd_parser(t_shell *shell);
int		is_builtin(char *cmd_name);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
char	*find_command_in_path(char *cmd_name, t_env *env);
int		handle_open_redir(t_redir *r);

void	close_fds(int in_fd, int out_fd);
int		iterate_redirs_and_open(t_redir *r, int *in_fd, int *out_fd);
int		apply_final_dups(int in_fd, int out_fd);
int		apply_redirs(t_cmd *cmd);
void	free_split(char **paths);

#endif