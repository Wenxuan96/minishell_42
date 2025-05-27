/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:21:14 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/27 10:39:10 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_ends(t_minishell *shell, t_process	*current)
{
	int	i;

	i = 0;
	if (shell->pipes == NULL)
		return ;
	while (i < shell->num_processes - 1)
	{
		if (shell->pipes[i][0] != current->input_fd)
			close(shell->pipes[i][0]);
		if (shell->pipes[i][1] != current->output_fd)
			close(shell->pipes[i][1]);
		i++;
	}
}

void	close_pipe_ends_parent(t_minishell *shell)
{
	int	i;

	i = 0;
	if (shell->pipes == NULL)
		return ;
	while (i < shell->num_processes - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}
