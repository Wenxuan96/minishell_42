/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:52 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/11 11:57:33 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;
	// int saved_stdin;
	// int saved_stdout;

	current = shell->process_list;
	// printf("current node: %s\n", current->command_arguments[0]);
	while (current != NULL)
	{
		if (current->is_builtin == 1 && shell->num_processes == 1 && !current->redirections)
		{
			// dprintf(2, "builtin in parent!\n");
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execute_builtin(current, shell);
			current->pid = 0;
			// ft_lstclear_process(&shell->process_list);
			// free_pipes(shell);
			// free_process(shell, current);
			// current->builtin->function(current, shell);
				// exit(g_exit_status);
		}
		else
		{
			// current->env_vars = copy_env_list(shell, current);
			// dprintf(2, "fokred!\n");
			pid = fork();
			if (pid < 0)
				return (display_shell_error("fork failed", 2), 0);
			else if (pid == 0)
			{
				// saved_stdin = dup(STDIN_FILENO);
				// saved_stdout = dup(STDOUT_FILENO);
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				// printf("child process running, pid: %d\n", getpid());
				if (current->is_builtin == 1)
				{
					// dprintf(2, "builtin!\n");
					if (execute_builtin(current, shell) == 0)
						exit(g_exit_status);
				}
				else
				{
					// dprintf(2, "cmd./!\n");
					if (execute_outside_cmd(current, shell) == 0)
						exit(g_exit_status);
				}
				free_process(shell, current);
				exit(EXEC_SUCCESS);
			}
			else
			{
				current->pid = pid;
			}
		}
		current = current->next_process;
	}
	// free_process(shell, current);
	close_pipe_ends_parent(shell);
	if (shell->num_processes >= 1)
		waitpid_children(shell);
	return (1);
}
