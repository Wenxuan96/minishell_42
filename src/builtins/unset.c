/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:10:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/06 17:45:55 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	unset_builtin(t_process *process, t_minishell *shell)
{
	t_environment	*current;
	t_environment	*prev;

	prev = NULL;
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_var, process->command_arguments[1]) == 0)
		{
			if (prev == NULL)
				shell->env_list = current->next_env_var;
			else
				prev->next_env_var = current->next_env_var;
			free(current->env_var);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next_env_var;
	}
	return (1);
}
