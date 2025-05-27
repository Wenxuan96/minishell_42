/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:54:47 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/27 13:24:10 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	exit_builtin(t_process *process, t_minishell *shell)
{
    int exit_code;
    
    if(process->command_arguments[2] != NULL)
    {
        display_shell_error(process, "exit: too many arguments", EXEC_FAILURE);
        return (0);
    }
    if (process->command_arguments[1] != NULL)
    {
        exit_code = ft_atoi(process->command_arguments[1]);
        ft_clean_exit(shell, exit_code);
    }
    return (1);  
}
