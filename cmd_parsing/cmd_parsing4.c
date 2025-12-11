/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 01:11:26 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 12:38:19 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	run_external_or_builtin_in_parent(t_cmd *cmd, t_shell *shell)
// {
// 	char	*cmd_path;
// 	char	**envp;

// 	if (cmd->redirs && apply_redirs(cmd) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(cmd->redirs->target, 2);
// 		write(2, ": ", 2);
// 		perror(""); //free_all(shell, NULL);
// 		return(shell->exit_code = 1, 1);
// 	}
// 	if (is_builtin(cmd->argv[0]))
// 	{
// 		return (shell->exit_code = (execute_builtin(cmd, shell) & 0xFF), 1);
// 		// free_all(shell, NULL);
// 	}
// 	cmd_path = find_command_in_path(cmd->argv[0], shell->env);
// 	if (cmd_path == NULL)
// 	{
// 		print_cmd_not_found(cmd->argv[0]);
// 		return(shell->exit_code = 127, 1);
// 		// exit((free_all(shell, NULL), 127));
// 	}
// 	envp = get_env_array(shell->env, 1);
// 	execve(cmd_path, cmd->argv, envp);
// 	print_execve_err(cmd_path);
// 	free(cmd_path);//, free_all(shell, envp), 126));
// 	return (shell->exit_code = 126, 126);
// }

int	run_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		shell->exit_code = 1;
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		run_external_or_builtin_in_child(cmd, shell);
		// child_process(pipefd, prev_fd, cur, shell);
	}
	signal_waiter(shell);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	// closing_fds(pipefd, prev_fd, cur->next);
	return (0);
}
void	my_execve(char *path, char **argv, char **envp, t_shell *shell)
{
	struct stat st;

    if (stat(path, &st) == 0)
    {
        if (S_ISDIR(st.st_mode))
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(": Is a directory\n", 2);
            // g_exit_status = 126;
			exit((free(path), free_all(shell, envp), 126));//126
        }
    }
    //;f (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		// return (1);
	// if  (execve(path, argv, envp) == -1)
	// {
    // 	// perror("minishell");

	// 	perror(path);
	// 	exit((free(path), free_all(shell, envp), 126));
	// }
	// exit((free(path), free_all(shell, envp), 1));


		
    // g_exit_status = 126;
	// exit((free(path), free_all(shell, envp), errno));//126
	///0000000000000
	if  (execve(path, argv, envp) == -1)
    {
        int exit_code = 126; // Default to 126 for typical execve failures (e.g., EACCES)
        
        // Handle "Command not found" or "No such file or directory" (exit 127)
        if (errno == ENOENT || errno == ENOTDIR)
            exit_code = 127;
        // You might need to check EFAULT too, but that's less common for shell execution.

        perror(path);
        exit((free(path), free_all(shell, envp), exit_code));
    }

	exit((free(path), free_all(shell, envp), 1));
	//0000000000000

}
