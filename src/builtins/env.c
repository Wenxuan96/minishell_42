/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanja <tanja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:42:33 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/31 07:40:56 by tanja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	env_builtin(t_process *process, t_minishell *shell)
{
	if (process->command_arguments[1] != NULL)
		return (display_shell_error(process, "env: too many arguments", EXEC_FAILURE), 0);
	prt_env_lst(shell->env_list);
	return (1);
}
