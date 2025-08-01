/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:26:37 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/06 17:46:42 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	free_pipes(t_minishell *shell);

void	ft_clean_exit(t_minishell *shell, int exit_code)
{
	ft_lstclear_env(&shell->env_list);
	ft_lstclear_process(&shell->process_list);
	if (shell->pipes)
		free_pipes(shell);
	shell = NULL;
	exit(exit_code);
}

void	free_pipes(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->num_processes - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
	shell->pipes = NULL;
}

void	prt_env_lst(t_environment *env_list)
{
	t_environment	*current;

	current = env_list;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			printf("%s=", current->env_var);
			printf("%s\n", current->value);
		}
		current = current->next_env_var;
	}
}
