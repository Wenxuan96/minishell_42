/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:10:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/06/06 17:33:32 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	unset_builtin(t_process *process, t_minishell *shell)
{
	t_environment	*current;
	t_environment	*prev;
	// t_environment	*to_del;
	
	prev = NULL;
	// (void)shell;
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_var, process->command_arguments[1]) == 0)
		{
			// to_del = current;
			if (prev == NULL)
			{
				shell->env_list = current->next_env_var;
				free(current->env_var);
				free(current->value);
				free(current);
				break ;
			}
			else
			{
				prev->next_env_var = current->next_env_var;
				free(current->env_var);
				free(current->value);
				free(current);
				break ;
			}
		}
		prev = current;
		current = current->next_env_var;
	}
	// prt_env_lst(&shell->env_list);
	return (1);
}
