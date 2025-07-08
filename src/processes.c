/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:52 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/08 11:23:27 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	exec_single_builtin(t_process *current, t_minishell *shell)
{
	setup_signals(0);
	execute_builtin(current, shell);
	shell->exit_status = current->exit_status;
	current->pid = 0;
	return (1);
}

int	exec_child(t_process *current, t_minishell *shell)
{
	int			status;
	
	setup_signals(1);
	if (current->is_builtin == 1)
	{
		if (execute_builtin(current, shell) == 0)
		{
			status = current->exit_status;
			free_process(shell, current);
			exit(status);
		}
	}
	else
	{
		if (execute_outside_cmd(current, shell) == 0)
		{
			status = current->exit_status;
			free_process(shell, current);
			exit(status);
		}
	}
	status = current->exit_status;
	free_process(shell, current);
	exit(0);
}

int	fork_children(t_process	*current, t_minishell *shell)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		return (display_shell_error(current, "fork failed", 2), 0);
	else if (pid == 0)
		exec_child(current, shell);
	else
		current->pid = pid;
	return (1);
}

int	create_processes(t_minishell *shell)
{
	t_process	*current;

	current = shell->process_list;
	while (current != NULL)
	{
		if (current->is_builtin == 1 && shell->num_processes == 1
			&& !current->redirections)
			exec_single_builtin(current, shell);
		else if (!fork_children(current, shell))
			return (0);
		current = current->next_process;
	}
	g_exit_status = 0;
	close_pipe_ends_parent(shell);
	if (shell->num_processes >= 1)
		waitpid_children(shell);
	return (1);
}
