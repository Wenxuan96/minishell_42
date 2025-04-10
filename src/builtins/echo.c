/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:08:01 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/10 15:19:37 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"


// char *p1_cmd[] = {"echo", "this is a test", NULL};
// char *p2_cmd[] = {"grep", "test", NULL};
// char *p3_cmd[] = {"wc", "-w", NULL};

// echo "this is a test" | grep test | wc -w


t_builtin   *new_builtin(t_builtin_type type, builtin_func *function)
{
    t_builtin *new_builtin;

    new_builtin = malloc(sizeof(t_builtin));
    new_builtin->type = type;
    new_builtin->function = function;
    return (new_builtin);
}

int echo_builtin(t_process *process) //-n -> not handled yet! how args after echo are parsed??
{
    t_process   *current;

    current = process;
    printf("the echo command: %s\n", current->command_arguments[0]);
    printf("builtin: %i\n", current->builtin->type);
    write(current->output_fd, current->command_arguments[1], ft_strlen(current->command_arguments[1]));
    write(current->output_fd, "\n", 1);
    return (1);
}

void    assign_builtin(t_process *process)
{
    t_process   *current;
    current = process;
    current->builtin = new_builtin(PWD, pwd_builtin);
    current->is_builtin = 1;
}
