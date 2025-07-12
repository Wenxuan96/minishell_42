/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:15:50 by tanja             #+#    #+#             */
/*   Updated: 2025/07/11 16:00:12 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

#include <sys/stat.h>

int	handle_builtin_redir(t_process *process, t_minishell *shell)
{
	if (process->redirections != NULL)
	{
		if (handle_redirection(process, shell) == 0)
			return (close_pipe_ends(shell, process), 0);
	}
	return (1);
}

int	handle_no_cmd(t_process *current, t_minishell *shell)
{
	if (current->input_fd != STDIN_FILENO)
		close(current->input_fd);
	if (current->output_fd != STDOUT_FILENO)
		close(current->output_fd);
	if (shell->pipes)
		close_pipe_ends(shell, current);
	return (1);
}

int	execute_dup(t_process *current, t_minishell *shell)
{
	// dprintf(2, "builtin: current->input_fd: %i\n", current->input_fd);
	if (dup2(current->input_fd, STDIN_FILENO) == -1)
	{
		display_shell_error(current, "in dup2 failed", EXEC_FAILURE);
		return (close_pipe_ends(shell, current), 0);
	}
	if (current->input_fd != STDIN_FILENO)
		close(current->input_fd);
	// dprintf(2, "builtint: current->output_fd: %i\n", current->output_fd);
	if (dup2(current->output_fd, STDOUT_FILENO) == -1)
	{
		printf("%i\n", current->output_fd);
		display_shell_error(current, "out dup2 failed", EXEC_FAILURE);
		return (close_pipe_ends(shell, current), 0);
	}
	if (current->output_fd != STDOUT_FILENO)
		close(current->output_fd);
	if (shell->pipes)
		close_pipe_ends(shell, current);
	return (1);
}

int	execute_builtin(t_process *process, t_minishell *shell)
{
	t_process	*current;

	current = process;
	// if (!handle_builtin_redir(current, shell))
	// 	return (0);
	if (current->redirections != NULL)
	{
		if (handle_redirection(current, shell) == 0)
			return (close_pipe_ends(shell, current), 0);
	}
	if (current->command_arguments[0] == NULL)
		handle_no_cmd(current, shell);
	else
	{
		if (execute_dup(current, shell) == 0)
			return (0);
		if (current->builtin->function(current, shell) == 0)
			return (0);
	}
	return (1);
}
