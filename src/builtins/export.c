/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:36:59 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/17 15:03:55 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int export_builtin(t_process *process)
{
    char   **split_vars;
    int     found;
    t_environment *current;

    found = 0;
    current = process->env_vars;
    if (process->command_arguments[1] == NULL)
    {
        prt_env_lst(process->env_vars);
        return (1);
    }
    split_vars = ft_split(process->command_arguments[1], '=');
    while (current != NULL)
    {
        if (ft_strcmp(current->env_var, split_vars[0]) == 0)
        {
            free(current->value);
            current->value = ft_strdup(split_vars[1]);
            found = 1;
        }
        current = current->next_env_var;
    }
    if (found == 0)
        ft_var_lstadd_back(&process->env_vars, ft_new_var_lst(split_vars[0], split_vars[1]));
    // prt_env_lst(&process->env_vars);
    // printf("\n\n\n");
    return (1);
}
