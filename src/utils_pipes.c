/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:19:04 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 13:07:46 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*new_process_lst(char **commands)
{
	t_process	*new_process;
	
	new_process = malloc(sizeof(t_process));
	new_process->command_arguments = allocate_array(commands);
	new_process->redirections= NULL;
	new_process->input_fd = -1;
	new_process->output_fd = -1;
	new_process->next_process= NULL;
	new_process->is_builtin = 0;
	new_process->is_pipeline = -1;
	new_process->builtin = NULL;
	new_process->stopped = 0;
	new_process->completed = 0;
	return (new_process);
}

void	process_lst_add_back(t_process   *new_process, t_process   **process_lst)
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
    t_process *current_process;
    int wait_res;
    
    current_process = shell->process_list;
    while (current_process != NULL)
    {
        wait_res = waitpid(current_process->pid, 0, 0);
        if (wait_res == -1)
        {
            perror("waitpid failed\n");
            exit(1);
        }
        current_process = current_process->next_process;
    }
}
