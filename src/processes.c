/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:52 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/29 11:05:58 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;
	int			status;

	status = -1;
	current = shell->process_list;
	while (current != NULL)
	{
		if (current->is_builtin == 1 && shell->num_processes == 1 && !current->redirections)
		{
			setup_signals(0);
			execute_builtin(current, shell);
			current->pid = 0;
		}
		else
		{
			pid = fork();
			if (pid < 0)
				return (display_shell_error(current, "fork failed", 2), 0);
			else if (pid == 0)
			{
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
				if (g_exit_status == 0)
					exit(status);
			}
			else
			{
				current->pid = pid;
			}
		}
		current = current->next_process;
	}
	close_pipe_ends_parent(shell);
	if (shell->num_processes >= 1)
		waitpid_children(shell);
	return (1);
}
