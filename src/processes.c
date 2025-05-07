/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:52 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/07 17:06:51 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;

	current = shell->process_list;
	// printf("current node: %s\n", current->command_arguments[0]);
	while (current != NULL)
	{
		if (current->is_builtin == 1 && shell->num_processes == 1 && !current->redirections)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execute_builtin(current, shell);
			// current->builtin->function(current, shell);
				// exit(g_exit_status);
		}
		else
		{
			// current->env_vars = copy_env_list(shell, current);
			pid = fork();
			if (pid < 0)
				return (display_shell_error("fork failed", 2), 0);
			else if(pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				// printf("child process running, pid: %d\n", getpid());
				if ((current->is_builtin == 1 && shell->num_processes > 1) || 
				(current->is_builtin == 1 && current->redirections != NULL))
				{
					if (execute_builtin(current, shell) == 0)
						exit(g_exit_status);
				}
				else if (current->is_builtin != 1 && current->redirections != NULL)
				{
					if (execute_outside_cmd(current, shell) == 0)
						exit(g_exit_status);
				}
				close_pipe_ends(shell, current);
				exit(EXEC_SUCCESS);
			}
			else
			{
				current->pid = pid;
			}
		}
		current = current->next_process;
	}
	close_pipe_ends_parent(shell);
	if (shell->num_processes > 1)
		waitpid_children(shell);
	return (1);
}
