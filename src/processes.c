/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:25:52 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/24 16:27:40 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;
	char		*path;
	char		**env_vars;

	current = shell->process_list;
	shell->num_processes = 3; //delete after parsing works!!!
	// printf("current node: %s\n", current->command_arguments[0]);
	while (current != NULL)
	{
		current->env_vars = copy_env_list(shell, current);
		pid = fork();
		if (pid < 0)
			return (perror("Forking failed"), 0);
		else if(pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (current->is_builtin == 1 && shell->num_processes > 1)
			{
				execute_builtin(current, shell);
			}
			// printf("input_fd: %i\n", current->input_fd);
			// printf("output_fd: %i\n", current->output_fd);
			else
			{
				handle_redirection(current);
				dup2(current->input_fd, STDIN_FILENO);
				dup2(current->output_fd, STDOUT_FILENO);
				close_pipe_ends(shell, current);
				path = get_path(current);
				env_vars = execve_get_envvars(current);
				// printf_twod(env_vars);
				execve(path, current->command_arguments, env_vars);
			}
			close_pipe_ends(shell, current);
			exit(0);
		}
		else
		{
			if (current->is_builtin == 1 && shell->num_processes == 1)
				execute_builtin(current, shell);	
			current->pid = pid;
			current = current->next_process;
		}
	}
	close_pipe_ends_parent(shell);
	waitpid_children(shell);
	return (1);
}
