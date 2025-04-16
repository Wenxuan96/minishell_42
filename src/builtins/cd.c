/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:54 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/16 13:01:15 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cd_builtin(t_process *process)
{
	char    *path;
    char    *new_path_buffer;
    int     len;

    path = process->command_arguments[1];
    chdir(path); //feed th efunciton env vars// update the vars
    new_path_buffer = getcwd(NULL, 0);
    while (process->env_vars != NULL)
    {
        len = ft_strlen(process->env_vars->env_var);
        if (ft_strncmp(process->env_vars->env_var,"PWD", len))
        {
            free(process->env_vars->value);
            process->env_vars->value = ft_strdup(new_path_buffer);
            // printf("new pwd: %s\n", process->env_vars->value);
            break;
        }
        process->env_vars = process->env_vars->next_env_var;
    }
    return (1);
}
