/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:54:47 by tignatov          #+#    #+#             */
/*   Updated: 2025/06/23 12:25:34 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	arg_is_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return(0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_process *process, t_minishell *shell)
{
	int exit_code;
	
	if(process->command_arguments[0] && process->command_arguments[1] && process->command_arguments[2] != NULL)
	{
		display_shell_error(process, "exit: too many arguments", EXEC_FAILURE);
		return (0);
	}
	if (process->command_arguments[0] && process->command_arguments[1] != NULL)
	{
		if (!arg_is_num(process->command_arguments[1]))
		{
			display_shell_error(process, "exit: numeric argument required", EXEC_FAILURE);
			return (0);
		}
		exit_code = ft_atoi(process->command_arguments[1]);
		ft_clean_exit(shell, exit_code);
	}
	else
		ft_clean_exit(shell, shell->exit_status);
	return (1);  
}
