/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanja <tanja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:54:47 by tignatov          #+#    #+#             */
/*   Updated: 2025/06/04 20:12:31 by tanja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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
        exit_code = ft_atoi(process->command_arguments[1]);
        ft_clean_exit(shell, exit_code);
    }
    else
        ft_clean_exit(shell, shell->exit_status);
    return (1);  
}
