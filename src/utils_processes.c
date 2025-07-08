/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:19:04 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/08 14:39:30 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	*copy_env_list(t_minishell *shell, t_process *process);

t_process	*new_process_lst(t_minishell *shell, char **commands)
{
	t_process	*new_process;

	(void)shell;
	new_process = malloc(sizeof(t_process));
	if (!new_process)
		return (NULL);
	new_process->command_arguments = allocate_array(commands);
	if (!new_process->command_arguments)
		return (NULL);
	new_process->redirections = NULL;
	new_process->env_vars = NULL;
	new_process->input_fd = -2;
	new_process->output_fd = -2;
	new_process->next_process = NULL;
	new_process->is_builtin = 0;
	new_process->is_pipeline = -1;
	new_process->builtin = NULL;
	new_process->completed = 0;
	new_process->exit_status = 0;
	return (new_process);
}

void	process_lst_add_back(t_process *new_process, t_process **process_lst)
{
	t_process	*current;

	if (*process_lst == NULL)
	{
		*process_lst = new_process;
		return ;
	}
	current = *process_lst;
	while (current->next_process != NULL)
		current = current->next_process;
	current->next_process = new_process;
}

void	waitpid_children(t_minishell *shell)
{
	t_process	*current_process;
	int			wait_res;
	int			status;

	current_process = shell->process_list;
	while (current_process != NULL)
	{
		if (current_process->pid != 0)
		{
			wait_res = waitpid(current_process->pid, &status, 0);
			while (wait_res == -1 && errno == EINTR)
				wait_res = waitpid(current_process->pid, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				g_exit_status = 130;
			else if (current_process->next_process == NULL)
			{
				if (WIFEXITED(status))
					g_exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					g_exit_status = 128 + WTERMSIG(status);
			}
		}
		current_process = current_process->next_process;
	}
}
