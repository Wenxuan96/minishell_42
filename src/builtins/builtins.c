/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:28:53 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/10 11:39:30 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"


// char *p1_cmd[] = {"echo", "this is a test", NULL};
// char *p2_cmd[] = {"grep", "test", NULL};
// char *p3_cmd[] = {"wc", "-w", NULL};

t_builtin   *new_builtin(t_builtin_type type, builtin_func *function)
{
    t_builtin *new_builtin;

    new_builtin = malloc(sizeof(t_builtin));
    new_builtin->type = type;
    new_builtin->function = function;
    return (new_builtin);
}

int echo_builtin(t_minishell *shell) //-n do not output the trailing new line
{
    printf("the echo command: %s\n", shell->process_list->command_arguments[0]);
    printf("builtin: %i\n", shell->process_list->builtin->type);
    return (1);
    
}

void    assign_builtin(t_process *process)
{
    t_process   *current;
    current = process;
    current->builtin = new_builtin(ECHO, echo_builtin);
    current->is_builtin = 1;
}
