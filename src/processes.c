/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:52 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/28 16:50:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;

	current = shell->process_list;
	shell->num_processes = 3; //delete after parsing works!!!
	// printf("current node: %s\n", current->command_arguments[0]);
	while (current != NULL)
	{
		// current->env_vars = copy_env_list(shell, current);
		pid = fork();
		if (pid < 0)
			return (display_shell_error("fork failed", 2), 0);
		else if(pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (current->is_builtin == 1 && shell->num_processes > 1)
			{
				if (execute_builtin(current, shell) == 0)
					exit(g_exit_status);
			}
			else
			{
				if (execute_outside_cmd(current, shell) == 0)
					exit(g_exit_status);
			}
			close_pipe_ends(shell, current);
			exit(EXEC_SUCCESS);
		}
		else
		{
			if (current->is_builtin == 1 && shell->num_processes == 1)
			{
				if (execute_builtin(current, shell) == 0)
					exit(g_exit_status);
			}
			current->pid = pid;
			current = current->next_process;
		}
	}
	close_pipe_ends_parent(shell);
	waitpid_children(shell);
	return (1);
}
