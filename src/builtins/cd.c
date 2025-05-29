/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:54 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/29 12:16:34 by tignatov         ###   ########.fr       */
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
    if (chdir(path) == -1)
        return(display_shell_error(process, "No such file or directory", EXEC_FAILURE), 0);
    new_path_buffer = getcwd(NULL, 0);
    if (!new_path_buffer)
        return(display_shell_error(process, "getcwd failed", EXEC_FAILURE), 0);
    while (shell->env_list != NULL)
    {
        len = ft_strlen(shell->env_list->env_var);
        if (ft_strncmp(shell->env_list->env_var,"PWD", len))
        {
            free(shell->env_list->value);
            shell->env_list->value = ft_strdup(new_path_buffer);
            if (!shell->env_list->value)
                return (free(new_path_buffer), display_shell_error(process, "memory allocation failed", EXEC_FAILURE), 0);
            // printf("new pwd: %s\n", shell->env_list->value);
            break;
        }
        shell->env_list = shell->env_list->next_env_var;
    }
    free(new_path_buffer);
    return (1);
}
