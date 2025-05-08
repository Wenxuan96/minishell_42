/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:08:01 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/08 16:33:37 by tignatov         ###   ########.fr       */
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

    (void)shell;
    current = process;
    // printf("the echo command: %s\n", current->command_arguments[0]);
    // printf("builtin: %i\n", current->builtin->type);
    write(STDOUT_FILENO, current->command_arguments[1], ft_strlen(current->command_arguments[1]));
    write(STDOUT_FILENO, "\n", 1);
    return (1);
}
