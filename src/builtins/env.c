/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:42:33 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/18 17:13:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	prt_env_lst_env(t_environment *env_list)
{
	t_environment	*current;

	current = env_list;
	while (current != NULL)
	{
		if (current->value != NULL && ft_strcmp(current->value, "") != 0)
		{
			printf("%s=", current->env_var);
			printf("%s\n", current->value);
		}
		current = current->next_env_var;
	}
}

int	env_builtin(t_process *process, t_minishell *shell)
{
	if (process->command_arguments[1] != NULL)
		return (display_shell_error(process, "env: too many arguments",
				EXEC_FAILURE), 0);
	prt_env_lst_env(shell->env_list);
	return (1);
}
