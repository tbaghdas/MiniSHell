/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:32:24 by ilya              #+#    #+#             */
/*   Updated: 2025/11/29 02:36:08 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *tok_type_to_str(t_toktyp t)
{
    if (t == WORD)       return "WORD";
    if (t == PIPE)       return "PIPE";
    if (t == REDIR_IN)   return "REDIR_IN";
    if (t == HEREDOC)    return "HEREDOC";
    if (t == REDIR_OUT)  return "REDIR_OUT";
    if (t == REDIR_APP)  return "REDIR_APP";
    return "UNKNOWN";
}

#include "../minishell.h"

void	launch_front_end(char *line)
{
	t_token		*tok_head;
	t_qstate	qs;
	t_cmd		*cmd_head;
	t_cmd		*cmd_cur;

	qs = QS_NONE;
	tok_head = NULL;
	cmd_head = NULL;
	cmd_cur = cmd_head;

	lexer(line, &tok_head, &qs);
	if (tok_head && tok_head->type == PIPE)
		syntax_errorer(tok_head->content);
	parser(tok_head, &cmd_cur);
	while (cmd_cur)
	{
		int i = 0;
		int n = 0;
		
		while (cmd_cur)
		{
			printf("cmd #%d\n", n);
			if (cmd_cur->argv[i])
			{
				while (cmd_cur->argv[i])
				{
					printf("argv[%d]: %s\n", i, cmd_cur->argv[i]);
					i++;
				}
			}
			if (cmd_cur->redirs)
			{
				while(cmd_cur->redirs)
				{
					printf("redir: type: %s, target: %s\n", tok_type_to_str(cmd_cur->redirs->type), cmd_cur->redirs->target);
					cmd_cur->redirs = cmd_cur->redirs->next;
				}
			}
			cmd_cur = cmd_cur->next;
			n++;
			i = 0;
		}
	}
}

int	main_loop()
{
	char	*line;

	while (1)
		{
			line = readline("minishell$ ");
			if (!line)
			{
				ft_putstr_fd("exit\n", STDOUT_FILENO);
				break;
			}
			if (*line)
				add_history(line);
			launch_front_end(line);
		}
		return 0;
}
