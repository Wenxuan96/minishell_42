/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:59:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 18:02:37 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	create_pipes(t_minishell *shell)
{
	t_process	*current;

	current = shell->process_list;
	if (shell->num_processes > 1)
	{
		while (current != NULL)
		{
			current->is_pipeline = 1;
			current = current->next_process;
		}
		shell->pipes = allocate_pipes(shell->num_processes - 1);
		if (!shell->pipes)
			exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
	}
	return (1);
}

int	assign_fd(t_minishell *shell)
{
	t_process	*current;
	int			i;

	current = shell->process_list;
	i = 0;
	while (current != NULL)
	{
		if (shell->num_processes > 1)
		{
			if (i == 0)
				current->input_fd = STDIN_FILENO;
			else
				current->input_fd = shell->pipes[i - 1][0];
			if (i == shell->num_processes - 1)
				current->output_fd = STDOUT_FILENO;
			else
				current->output_fd = shell->pipes[i][1];
			i++;
		}
		current = current->next_process;
	}
	return (1);
}
