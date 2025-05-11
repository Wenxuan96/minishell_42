/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:54 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/11 10:57:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cd_builtin(t_process *process, t_minishell *shell)
{
	char    *path;
    char    *new_path_buffer;
    int     len;

    (void)shell;
    path = process->command_arguments[1];
    chdir(path);
    new_path_buffer = getcwd(NULL, 0);
    while (shell->env_list != NULL)
    {
        len = ft_strlen(shell->env_list->env_var);
        if (ft_strncmp(shell->env_list->env_var,"PWD", len))
        {
            free(shell->env_list->value);
            shell->env_list->value = ft_strdup(new_path_buffer);
            // printf("new pwd: %s\n", shell->env_list->value);
            break;
        }
        shell->env_list = shell->env_list->next_env_var;
    }
    return (1);
}
