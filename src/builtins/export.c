/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:36:59 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/16 13:34:47 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int export_builtin(t_process *process)
{
    char   **split_vars;
    int     found;

    found = 0;
    if (process->command_arguments[1] == NULL)
        prt_env_lst(&process->env_vars);
    split_vars = ft_split(process->command_arguments[1], '=');
    while (process->env_vars !=NULL)
    {
        if (ft_strcmp(process->env_vars->env_var, split_vars[0]) == 0)
        {
            process->env_vars->value = split_vars[1];
            found = 1;
        }
        process->env_vars = process->env_vars->next_env_var;
    }
    if (found == 0)
        ft_var_lstadd_back(&process->env_vars, ft_new_var_lst(split_vars[0], split_vars[1]));
    prt_env_lst(&process->env_vars);
    return (1);
}
