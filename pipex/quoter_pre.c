/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter_pre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:14:56 by ilya              #+#    #+#             */
/*   Updated: 2025/08/09 00:19:32 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	quot_esc_checker(char *arg)
{
	int	i;
	int	in_sq;
	int	in_dq;
	int	has_special;

	i = -1;
	in_sq = 0;
	in_dq = 0;
	has_special = 0;
	while (arg[++i])
	{
		if (arg[i] == '\'' && (!in_dq) && (i == 0 || arg[i - 1] != '\\' ))
			in_sq = !in_sq;
		else if (arg[i] == '\"' && (!in_sq) && (i == 0 || arg[i - 1] != '\\'))
			in_dq = !in_dq;
		else if (arg[i] == '\\')
			has_special = 1;
		else if (arg[i] == ' ' && (in_sq || in_dq))
			has_special = 1;
	}
	if ((!ft_strncmp(arg, "./", 2) && ft_strchr(arg, ' ')) || has_special)
		return (1);
	if ((!in_sq) && (!in_dq))
		return (0);
	return (-1);
}

static void	quote_stater(char c, char *s, t_space_ctx *ctx)
{
	if (c == '\'' && !(ctx->in_dq) && (ctx->i == 0
			|| s[ctx->i - 1] != '\\'))
		ctx->in_sq = !(ctx->in_sq);
	else if (c == '\"' && !(ctx->in_sq) && (ctx->i == 0
			|| s[ctx->i - 1] != '\\'))
		ctx->in_dq = !(ctx->in_dq);
}

static void	space_handler(char *buf, t_space_ctx *ctx)
{
	if ((ctx->in_sq || ctx->in_dq))
		buf[ctx->i] = '\x01';
	else if (!(ctx->first_space_protected) && ctx->is_path)
	{
		buf[ctx->i] = '\x01';
		ctx->first_space_protected = 1;
	}
}

static char	*space_replacer(char *arg)
{
	t_space_ctx	ctx;
	char		*buf;

	ctx = (t_space_ctx){0};
	buf = ft_strdup(arg);
	if (!buf)
		return (NULL);
	ctx.in_sq = 0;
	ctx.in_dq = 0;
	ctx.first_space_protected = 0;
	ctx.is_path = is_direct_path(buf);
	ctx.i = 0;
	while (buf[ctx.i])
	{
		quote_stater(arg[ctx.i], arg, &ctx);
		if (buf[ctx.i] == ' ')
			space_handler(buf, &ctx);
		ctx.i++;
	}
	return (buf);
}

char	**space_prot_splitter(char *arg)
{
	char	**buf_arr;
	char	*buf_str;
	int		check;

	buf_arr = NULL;
	check = quot_esc_checker(arg);
	if (!check)
	{
		buf_arr = ft_split(arg, ' ');
		if (!buf_arr)
			return (perror("./pipex: malloc"), NULL);
	}
	else if (check == -1)
		return (NULL);
	else if (check == 1)
	{
		buf_str = space_replacer(arg);
		if (!buf_str)
			return (perror("./pipex: malloc"), NULL);
		buf_arr = ft_split(buf_str, ' ');
		free(buf_str);
	}
	return (buf_arr);
}
