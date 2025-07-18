/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:10:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/18 14:48:39 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	free_envvar(t_environment *current)
{
	free(current->env_var);
	free(current->value);
	free(current);
}

int	unset_builtin(t_process *process, t_minishell *shell)
{
	t_environment	*current;
	t_environment	*prev;
	int				i;

	i = 0;
	while (process->command_arguments[++i] != NULL)
	{
		prev = NULL;
		current = shell->env_list;
		while (current != NULL)
		{
			if (ft_strcmp(current->env_var, process->command_arguments[i]) == 0)
			{
				if (prev == NULL)
					shell->env_list = current->next_env_var;
				else
					prev->next_env_var = current->next_env_var;
				free_envvar(current);
				break ;
			}
			prev = current;
			current = current->next_env_var;
		}
	}
	return (1);
}
