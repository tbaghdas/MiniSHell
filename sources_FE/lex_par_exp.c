/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_par_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:32:24 by ilya              #+#    #+#             */
/*   Updated: 2025/12/06 19:06:33 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*tok_type_to_str(t_toktyp t)
// {
// 	if (t == WORD)
// 		return ("WORD");
// 	if (t == PIPE)
// 		return ("PIPE");
// 	if (t == REDIR_IN)
// 		return ("REDIR_IN");
// 	if (t == HEREDOC)
// 		return ("HEREDOC");
// 	if (t == REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (t == REDIR_APP)
// 		return ("REDIR_APP");
// 	return ("UNKNOWN");
// }

// void	print_cmds(t_shell *sh)
// {
// 	int		i;
// 	int		n;
// 	char	*line;
// 	t_cmd	*cmd_cur;
// 	t_redir	*rd;

// 	cmd_cur = sh->cmd;
// 	rd = sh->cmd->redirs;
// 	while (cmd_cur)
// 	{
// 		i = 0;
// 		n = 0;
// 		while (cmd_cur)
// 		{
// 			printf("cmd #%d\n", n);
// 			if (cmd_cur->argv[i])
// 			{
// 				while (cmd_cur->argv[i])
// 				{
// 					printf("argv[%d]: %s\n", i, cmd_cur->argv[i]);
// 					i++;
// 				}
// 			}
// 			if (rd)
// 			{
// 				while (rd)
// 				{
// 					printf("redir: type: %s, target: %s\n",
// 						tok_type_to_str(rd->type),
// 						rd->target);
// 					if (rd->type == HEREDOC)
// 					{
// 						printf("content:\n");
// 						line = get_next_line(rd->fd);
// 						while (line)
// 						{
// 							printf("%s", line);
// 							free(line);
// 							line = get_next_line(rd->fd);
// 						}
// 					}
// 					rd = rd->next;
// 				}
// 			}
// 			cmd_cur = cmd_cur->next;
// 			if (cmd_cur)
// 				rd = cmd_cur->redirs;
// 			n++;
// 			i = 0;
// 		}
// 	}
// }

int	parse_input(t_shell *sh, char **envp, char *line)
{
	t_qstate	qs;
	t_env		env;

	(void)envp;
	(void)env;
	qs = NONE;
	lexer(line, sh, &qs);
	if (sh->tok && sh->tok->type == PIPE)
		return (syntax_errorer(sh->tok->content, sh), 1);
	if (parser(sh->tok, sh))
		return (1);
	expander(sh);
	return (0);
}
