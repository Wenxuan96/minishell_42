/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:09:16 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 10:32:11 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

/*
    echo
    pwd
    cd
    export
    unset
    env
    exit
*/

t_builtin   *new_builtin(t_builtin_type type, builtin_func *function)
{
    t_builtin *new_builtin;

    new_builtin = malloc(sizeof(t_builtin));
    new_builtin->type = type;
    new_builtin->function = function;
    return (new_builtin);
}

void    assign_builtin(t_process *process)
{
    t_process   *current;
    current = process;
    current->builtin = new_builtin(PWD, pwd_builtin);
    current->is_builtin = 1;
}
