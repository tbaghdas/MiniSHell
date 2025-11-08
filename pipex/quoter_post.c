/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_post.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 03:12:35 by ilya              #+#    #+#             */
/*   Updated: 2025/08/09 00:19:14 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	quotes_handler(t_qe_ctx *qe_ctx, char *arg)
{
	if (arg[qe_ctx->i] == '\'')
	{
		qe_ctx->in_single = !qe_ctx->in_single;
		qe_ctx->i++;
	}
	else if (arg[qe_ctx->i] == '"')
	{
		qe_ctx->in_double = !qe_ctx->in_double;
		qe_ctx->i++;
	}
}

static void	backslash_dq(t_qe_ctx *qe_ctx, char next, char *buf, char *arg)
{
	if (next && (next == '"' || next == '$' || next == '`'
			|| next == '\\' || next == '\n'))
	{
		qe_ctx->i++;
		buf[qe_ctx->j++] = arg[qe_ctx->i++];
	}
	else
		buf[qe_ctx->j++] = arg[qe_ctx->i++];
}

static void	backslash(t_qe_ctx *qe_ctx, char next, char *buf, char *arg)
{
	if (next)
	{
		qe_ctx->i++;
		buf[qe_ctx->j++] = arg[qe_ctx->i++];
	}
	else
		buf[qe_ctx->j++] = arg[qe_ctx->i++];
}

static void	backslash_handler(t_qe_ctx *qe_ctx, char *buf, char *arg)
{
	char	next;

	next = arg[qe_ctx->i + 1];
	if (qe_ctx->in_single)
		buf[qe_ctx->j++] = arg[qe_ctx->i++];
	else if (qe_ctx->in_double)
		backslash_dq(qe_ctx, next, buf, arg);
	else
		backslash(qe_ctx, next, buf, arg);
}

char	*quot_escape_remover(char *arg)
{
	char		*buf;
	t_qe_ctx	qe_ctx;

	qe_ctx = (t_qe_ctx){0};
	buf = malloc((ft_strlen(arg) + 1) * sizeof(char));
	if (!buf)
		return (perror("./pipex: malloc"), NULL);
	while (arg[qe_ctx.i])
	{
		if ((arg[qe_ctx.i] == '\'' && !qe_ctx.in_double)
			|| (arg[qe_ctx.i] == '"' && !qe_ctx.in_single
				&& !(qe_ctx.i > 0 && arg[qe_ctx.i - 1] == '\\')))
		{
			quotes_handler(&qe_ctx, arg);
			continue ;
		}
		if (arg[qe_ctx.i] == '\\')
		{
			backslash_handler(&qe_ctx, buf, arg);
			continue ;
		}
		buf[qe_ctx.j++] = arg[qe_ctx.i++];
	}
	return (buf[qe_ctx.j] = '\0', buf);
}
