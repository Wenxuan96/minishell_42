/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:21:55 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/05 18:32:38 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_fds(t_minishell *shell)
{
	t_process	*current;

	current = shell->process_list;
	while (current != NULL)
	{
		printf("\n\nProcess: %i\n", current->pid);
		printf("read end: %i\n", current->input_fd);
		printf("write end: %i\n\n", current->output_fd);
		current = current->next_process;
	}
}

void	printf_twod(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
