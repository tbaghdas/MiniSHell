/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:10:42 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 12:57:22 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_parser(t_shell *shell)
{
	int		ret;
	t_cmd	*cmd;
	int		i;

	if (shell == NULL)
		return (1);
	cmd = shell->cmd;
	if (cmd == NULL || (cmd->argv == NULL || cmd->argv[0] == NULL))
		return (1);

	// i = 0;
	// command = cmd->argv[0];
	// while (cmd->argv[i] && cmd->argv[i][0] == '\0')
	// 	i++;
	// if (cmd->argv[i])
	// 	command = cmd->argv[i];

i = 0;
int j = 0;

/* Count empty leading args */
while (cmd->argv[i] && cmd->argv[i][0] == '\0')
{
    free(cmd->argv[i]);   // FREE THE EMPTY STRING
    i++;
}

/* If we removed some, shift others left */
if (i > 0)
{
    while (cmd->argv[i])
    {
        cmd->argv[j] = cmd->argv[i];
        j++;
        i++;
    }
    cmd->argv[j] = NULL;
}

/* If everything was empty → no command */
if (cmd->argv[0] == NULL)
    return (0);


	
 	if (cmd->next == NULL && is_builtin(cmd->argv[0]) == 1)
	{
		int original_stdout = dup(STDOUT_FILENO);
		int original_stdin = dup(STDIN_FILENO);
		apply_redirs(cmd);
		execute_builtin(cmd, shell);
		dup2(original_stdout, 1);
		close(original_stdout);
		dup2(original_stdin, 0);
		close(original_stdin);
		return (shell->exit_code);
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
		return (built_in_cd(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (built_in_echo(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (built_in_env(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (built_in_exit(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (built_in_export(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (built_in_pwd(shell));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (built_in_unset(cmd->argv, shell));
	return (0);
}

char	*find_command_in_path(char *cmd_name, t_env *env)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	*path_value;
	char	*temp;

	path_value = ft_getenv("PATH", env);
	if (path_value == NULL || ft_strchr(cmd_name, '/') || !cmd_name
		|| !cmd_name[0])
		return (ft_strdup(cmd_name));
	paths = ft_split(path_value, ':');
	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		temp = ft_strjoin(full_path, cmd_name);
		free(full_path);
		full_path = temp;
		if (access(full_path, F_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
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
		return (r->fd);
	return (-2);
}
