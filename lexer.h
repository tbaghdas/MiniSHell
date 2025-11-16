/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:04:05 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/16 02:13:47 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

typedef enum e_toktyp
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APP,
	TOK_HEREDOC	
} t_toktyp;

typedef enum e_qstate
{
	QS_NONE,
	QS_SINGLE,
	QS_DOUBLE
} t_qstate;

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
	int				do_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

int		is_escaping(t_qstate qs, char c);
int		is_op_start(char c);
void	qstate_updater(char c, t_qstate *qs);
void	mint_op_token(char* line, t_token **tokhead, size_t* i, int len);
int		op_len(char *s);
t_token	*tok_lst_new(t_toktyp type, char *content);
void	tok_lstadd_back(t_token **lst, t_token *new_node);
void	tok_lstclear(t_token **lst, void (*del)(void*));
void	word_end(char* line, t_token **tokhead, size_t i, size_t init);
void	word_start(char *line, t_qstate *qs, t_token **tokhead, size_t *i);

#endif