/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanja <tanja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:54 by tignatov          #+#    #+#             */
/*   Updated: 2025/06/04 19:24:00 by tanja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cd_builtin(t_process *process, t_minishell *shell)
{
	char    *path;
    char    *new_path_buffer;
    int     len;
    t_environment   *env_list;

    path = NULL;
    if (process->command_arguments[1] != NULL && process->command_arguments[2] != NULL)
        return(display_shell_error(process, "cd: too many arguments", EXEC_FAILURE), 0);
    if (process->command_arguments[1] == NULL)
    {
        env_list = shell->env_list;
        while (env_list != NULL)
        {
            if (ft_strcmp(env_list->env_var, "HOME") == 0)
            {
                path = env_list->value;
                break ;
            }
            env_list = env_list->next_env_var;
        }
        if (!path)
            return (display_shell_error(process, "cd: HOME does not exist", EXEC_FAILURE), 0);
    }
    else
        path = process->command_arguments[1];
    if (chdir(path) == -1)
    {
        if (errno == ENOENT)
            return (display_shell_error(process, "cd: no such file or directory", EXEC_FAILURE), 0);
        else if (errno == EACCES)
            return (display_shell_error(process, "cd: permission denied", EXEC_FAILURE), 0);
        else if (errno == ENOTDIR)
            return (display_shell_error(process, "cd: not a directory", EXEC_FAILURE), 0);
        else
            return (display_shell_error(process, "cd: error", EXEC_FAILURE), 0);
    }
    new_path_buffer = getcwd(NULL, 0);
    if (!new_path_buffer)
        return(display_shell_error(process, "cd: getcwd failed", EXEC_FAILURE), 0);
    while (shell->env_list != NULL)
    {
        len = ft_strlen(shell->env_list->env_var);
        if (ft_strncmp(shell->env_list->env_var,"PWD", len))
        {
            free(shell->env_list->value);
            shell->env_list->value = ft_strdup(new_path_buffer);
            if (!shell->env_list->value)
                return (free(new_path_buffer), display_shell_error(process, "cd: memory allocation failed", EXEC_FAILURE), 0);
            // printf("new pwd: %s\n", shell->env_list->value);
            break;
        }
        shell->env_list = shell->env_list->next_env_var;
    }
    free(new_path_buffer);
    return (1);
}
