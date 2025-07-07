/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outside_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:58:57 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 12:33:16 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	handle_outside_redir(t_process *process, t_minishell *shell)
{
	if (process->redirections != NULL)
	{
		if (handle_redirection(process, shell) == 0)
			return (close_pipe_ends(shell, process), 0);
	}
	return (1);
}

void	handle_no_cmd2(t_process *current, t_minishell *shell)
{
	if (current->input_fd != STDIN_FILENO)
		close(current->input_fd);
	if (current->output_fd != STDOUT_FILENO)
		close(current->output_fd);
	if (shell->pipes)
		close_pipe_ends(shell, current);
}

int	execute_dup2(t_process *current, t_minishell *shell)
{
	if (dup2(current->input_fd, STDIN_FILENO) == -1)
	{
		display_shell_error(current, "dup2 failed", EXEC_FAILURE);
		return (close_pipe_ends(shell, current), 0);
	}
	if (current->input_fd != STDIN_FILENO)
		close(current->input_fd);
	if (dup2(current->output_fd, STDOUT_FILENO) == -1)
	{
		display_shell_error(current, "dup2 failed", EXEC_FAILURE);
		return (close_pipe_ends(shell, current), 0);
	}
	if (current->output_fd != STDOUT_FILENO)
		close(current->output_fd);
	if (shell->pipes)
		close_pipe_ends(shell, current);
	return (1);
}

int	execute_outside_cmd(t_process *process, t_minishell *shell)
{
	t_process	*current;
	char		*path;
	char		**env_vars;

	current = process;
	if (handle_outside_redir(current, shell) == 0)
		return (0);
	if (current->command_arguments[0] == NULL)
		handle_no_cmd2(current, shell);
	else
	{
		if (execute_dup2(current, shell) == 0)
			return (0);
		path = get_path(shell, process);
		if (!path)
			return (close_pipe_ends(shell, current), 0);
		env_vars = execve_get_envvars(shell);
		execve(path, current->command_arguments, env_vars);
	}
	return (1);
}
