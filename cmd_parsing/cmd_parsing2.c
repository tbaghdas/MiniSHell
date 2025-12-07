/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:10:42 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/07 19:16:57 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_parser(t_shell *shell)
{
	char	*cmd_path;
	int		ret;
	t_cmd	*cmd;

	if (shell == NULL)
		return (1);
	cmd = shell->cmd;
	if (cmd == NULL || (cmd->argv == NULL || cmd->argv[0] == NULL)
		&& (cmd->redirs == NULL
			|| cmd->redirs != NULL && cmd->redirs->fd == -1))
		return (1);
	if (cmd->redirs != NULL && cmd->redirs->fd != -1)
	{
		return (run_external_or_builtin_in_child(cmd, shell));
		//apply_redirs(cmd);//////////////////////////////////
	}
	if (cmd->next == NULL && is_builtin(cmd->argv[0]) == 1
		&& cmd->redirs == NULL)
	{
		return (execute_builtin(cmd, shell));
	}
	ret = execute_pipeline(cmd, shell);
	return (ret);
}

int	is_builtin(char *cmd_name)
{
	if (cmd_name == NULL)
		return (0);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL)
		return (-1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtinexit(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, shell));
	return (0);
}

char	*find_command_in_path(char *cmd_name, t_env *env)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	*path_value;

	path_value = get_env_value("PATH", env);
	if (path_value == NULL)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd_name);
		if (access(full_path, F_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (free_split(paths), NULL);
}

int	handle_open_redir(t_redir *r)
{
	if (r->type == REDIR_IN)
		return (open(r->target, O_RDONLY));
	else if (r->type == REDIR_OUT)
		return (open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 00644));
	else if (r->type == REDIR_APP)
		return (open(r->target, O_WRONLY | O_CREAT | O_APPEND, 00644));
	else if (r->type == HEREDOC)
		return (open(r->fd, O_WRONLY | O_CREAT | O_APPEND, 00644));
	return (-2);
}
