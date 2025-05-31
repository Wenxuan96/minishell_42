/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanja <tanja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:36:59 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/31 07:46:22 by tanja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int is_valid_env(char *var)
{
    int i;

    i = 0;
    while (var[i])
    {
        if (!ft_isalpha(var[i]))
            return(0);
        i++;
    }
    return (1);
}

int export_builtin(t_process *process, t_minishell *shell)
{
    char   **split_vars;
    int     found;
    t_environment *current;

    found = 0;
    // (void)process;
    current = shell->env_list;
    if (process->command_arguments[1] == NULL)
    {
        prt_env_lst(shell->env_list);
        return (1);
    }
    split_vars = ft_split(process->command_arguments[1], '=');
    dprintf(2, "split[0]: %s\n", split_vars[0]);
    if (is_valid_env(split_vars[0]) && split_vars[0])
    {
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
            ft_var_lstadd_back(&shell->env_list, ft_new_var_lst(split_vars[0], split_vars[1]));
        free(split_vars);
        // prt_env_lst(&shell->env_list);
        // printf("\n\n\n");
        return (1);
    }
    else
        return (display_shell_error(process, "export: not a valid identifier", EXEC_FAILURE), 0);
}
