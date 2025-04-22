/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:10:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/22 13:30:17 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int unset_builtin(t_process *process, t_minishell *shell)
{
    t_environment   *current;
    t_environment   *prev;
    // t_environment   *to_del;
    
    prev = NULL;
    (void)shell;
    current = process->env_vars;
    while (current != NULL)
    {
        if (ft_strcmp(current->env_var, process->command_arguments[1]) == 0)
        {
            // to_del = current;
            if (prev == NULL)
            {
                process->env_vars = current->next_env_var;
                free(current->env_var);
                free(current->value);
                free(current);
                break ;
            }
            else
            {
                prev->next_env_var = current->next_env_var;
                free(current->env_var);
                free(current->value);
                free(current);
                break ;
            }
        }
        prev = current;
        current = current->next_env_var;
    }
    // prt_env_lst(&process->env_vars);
    return (1);
}
