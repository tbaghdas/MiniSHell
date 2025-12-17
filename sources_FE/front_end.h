/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_end.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:04:05 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:26 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRONT_END_H
# define FRONT_END_H

# define VAR_NAME_MAX 256

typedef struct s_shell	t_shell;

typedef enum e_toktyp
{
	WORD,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_APP,
}	t_toktyp;

typedef enum e_qstate
{
	NONE,
	SINGLE,
	DOUBLE
}	t_qstate;

typedef struct s_token
{
	t_toktyp		type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_toktyp		type;
	char			*target;
	int				fd;
	struct s_redir	*next;
	int				do_expand;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

//LEXER
void	print_tokens(t_shell *sh);
int		lexer(char *line, t_shell *sh, t_qstate *qs);
int		is_op_start(char c);
void	qstate_updater(char c, t_qstate *qs);
int		op_len(char *s);
int		ft_isspace(char c);

//tokenizer
void	mint_op_token(char *line, t_token **tokhead, size_t *i, int len);
void	word_end(char *line, t_token **tokhead, size_t i, size_t init);
void	word_start(char *line, t_qstate *qs, t_token **tokhead, size_t *i);

//token list utils
t_token	*tok_lst_new(t_toktyp type, char *content);
void	tok_lstadd_back(t_token **lst, t_token *new_node);
void	tok_lstclear(t_token **lst, void (*del)(void*));

//PARSER
int		parser(t_token *tok, t_shell *sh);
int		count_pipes(t_token *tok);
int		all_tokens_handler(t_token **tok, t_cmd **cmd_cur, t_shell *sh);

//redir utils
int		is_input_redir(t_toktyp type);
int		is_output_redir(t_toktyp type);
//redir list utils
t_redir	*redir_lst_new(t_token *tok);
void	redir_lstadd_back(t_redir **lst, t_redir *new_node);
void	redir_lstclear(t_redir **lst, void (*del)(void*));

//cmd utils
int		word_counter(t_token *tok_head);
//cmd list utils
t_cmd	*cmd_lst_new(void);
void	cmd_lstadd_back(t_cmd **lst, t_cmd *new_node);
void	cmd_lstclear(t_cmd **lst, void (*del)(void*));

//HEREDOC
int		process_heredoc(t_shell *sh);
//heredoc utils
void	heredoc_sigint_handler(int sig);
void	signal_waiter(pid_t last, t_shell *sh);
int		wait_heredoc_child(pid_t pid, t_shell *sh);

//EXPANDER
void	actual_expander(char **line, t_shell *sh, t_toktyp t);
void	expander(t_shell *sh);
//expander utils
void	env_extractor(char **line, char **buf, t_shell *sh);
int		exit_coder(char **src, char **dst, t_shell *sh);
int		expand_needed(char *s, t_qstate qs, t_toktyp type);
void	handle_cmds(t_shell *sh);
void	handle_redirs(t_shell *sh);
void	heredoc_expander(char **line, t_shell *sh);
int		legit(char c);
int		quote_changes(char c, t_qstate qs);

//error & clean-up utils & debug
void	fatal_error(char *line, t_shell *sh);
void	syntax_errorer_quotes(t_qstate qs, t_shell *sh);
void	syntax_errorer_redirs(char *line, t_shell *sh);
void	syntax_errorer_heredoc(t_redir *rd, t_shell *sh);

#endif