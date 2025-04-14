/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:19:04 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 12:49:14 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
