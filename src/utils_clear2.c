/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clear2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:31:22 by wxi               #+#    #+#             */
/*   Updated: 2025/07/14 14:00:16 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "minishell.h"

void	close_process_pipes(t_process *current)
{
	if (current->input_fd != STDIN_FILENO && current->input_fd != -1)
		close(current->input_fd);
	if (current->output_fd != STDOUT_FILENO && current->output_fd != -1)
		close(current->output_fd);
}

void	ft_lstclear_process(t_process **process_list)
{
	t_process	*current;
	t_process	*next;
	int			i;

	if (!process_list || !*process_list)
		return ;
	current = *process_list;
	while (current)
	{
		next = current->next_process;
		ft_lstclear_redir(&current->redirections);
		if (current->command_arguments)
		{
			i = 0;
			while (current->command_arguments[i])
				free(current->command_arguments[i++]);
			free(current->command_arguments);
		}
		if (current->is_builtin && current->builtin)
			free(current->builtin);
		close_process_pipes(current);
		free(current);
		current = next;
	}
	*process_list = NULL;
}

