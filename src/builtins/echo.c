/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:08:01 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/21 15:03:31 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"


// char *p1_cmd[] = {"echo", "this is a test", NULL};
// char *p2_cmd[] = {"grep", "test", NULL};
// char *p3_cmd[] = {"wc", "-w", NULL};

// echo "this is a test" | grep test | wc -w


int echo_builtin(t_process *process, t_minishell *shell) //-n -> not handled yet! how args after echo are parsed??
{
    t_process   *current;
    int i;

    (void)shell;
    current = process;
    if (current->command_arguments[1] == NULL)
        return (1);
    if (ft_strcmp(current->command_arguments[1], "-n") == 0)
    {
        i = 2;
        while (current->command_arguments[i] != NULL)
        {
            write(STDOUT_FILENO, current->command_arguments[i], ft_strlen(current->command_arguments[i]));
            i++;   
            if (current->command_arguments[i] != NULL)
                write(STDOUT_FILENO, " ", 1);
        }
    }
    else
    {
        i = 1;
        while (current->command_arguments[i] != NULL)
        {
            write(STDOUT_FILENO, current->command_arguments[i], ft_strlen(current->command_arguments[i]));
            i++;
            if (current->command_arguments[i] != NULL)
                write(STDOUT_FILENO, " ", 1);
        }
        write(STDOUT_FILENO, "\n", 1);
    }
    return (1);
}
