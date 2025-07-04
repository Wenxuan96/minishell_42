/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:15:50 by tanja             #+#    #+#             */
/*   Updated: 2025/07/04 14:44:38 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	execute_builtin(t_process *process, t_minishell *shell)
{
	t_process	*current;

	current = process;
	if (current->redirections != NULL)
	{
		if (handle_redirection(current, shell) == 0)
			return (close_pipe_ends(shell, current), 0);
	}
	if (current->command_arguments[0] == NULL)
	{
		if (current->input_fd != STDIN_FILENO)
			close(current->input_fd);
		if (current->output_fd != STDOUT_FILENO)
			close(current->output_fd);
		if (shell->pipes)
			close_pipe_ends(shell, current);
	}
	else
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
		// dprintf(2, "outout fd: %i\n", current->output_fd);
		if (current->output_fd != STDOUT_FILENO)
			close(current->output_fd);
		if (shell->pipes)
			close_pipe_ends(shell, current);
		if (current->builtin->function(current, shell) == 0)
			return (0);
	}
	return (1);
}

int	execute_outside_cmd(t_process *process, t_minishell *shell)
{
	t_process	*current;
	char		*path;
	char		**env_vars;

	current = process;
	if (current->redirections != NULL)
	{
		if (handle_redirection(current, shell) == 0)
			return (close_pipe_ends(shell, current), 0);
	}
	if (current->command_arguments[0] == NULL)
	{
		if (current->input_fd != STDIN_FILENO)
			close(current->input_fd);
		if (current->output_fd != STDOUT_FILENO)
			close(current->output_fd);
		if (shell->pipes)
			close_pipe_ends(shell, current);
	}
	else
	{
		if (dup2(current->input_fd, STDIN_FILENO) == -1)
		{
			display_shell_error(current, "dup2 failed", EXEC_FAILURE);
			return (close_pipe_ends(shell, current), 0);
		}
		// dprintf(2, "input fd: %i\n", current->input_fd);
		if (current->input_fd != STDIN_FILENO)
			close(current->input_fd);
		if (dup2(current->output_fd, STDOUT_FILENO) == -1)
		{
			display_shell_error(current, "dup2 failed", EXEC_FAILURE);
			return (close_pipe_ends(shell, current), 0);
		}
		// dprintf(2, "outout fd: %i\n", current->output_fd);
		if (current->output_fd != STDOUT_FILENO)
			close(current->output_fd);
		if (shell->pipes)
			close_pipe_ends(shell, current);
		path = get_path(shell, process);
		if (!path)
		{
			// display_shell_error(current, "memory allocation failed", EXEC_FAILURE);
			return (close_pipe_ends(shell, current), 0);
		}
		env_vars = execve_get_envvars(shell);
		// if (!env_vars)
		// 	return (display_shell_error(current, "memory allocation failed", EXEC_FAILURE),
		// 		close_pipe_ends(shell, current), 0);
		execve(path, current->command_arguments, env_vars);
	}
	return (1);
}
