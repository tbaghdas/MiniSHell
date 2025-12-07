/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_end.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:04:05 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/08 01:27:22 by ikiriush         ###   ########.fr       */
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

//EXPANDER
int		env_extractor(char *line, char *buf, int *i, int *j);
void	expander(t_shell *sh);
void	heredoc_expander(char **line, t_shell *sh);
int		legit(char c);

//error & clean-up utils & debug
void	fatal_error(char *line, t_shell *sh);
void	syntax_errorer_quotes(t_qstate qs, t_shell *sh);
void	syntax_errorer_redirs(char *line, t_shell *sh);

#endif