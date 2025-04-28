/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_get_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:42 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/28 16:43:54 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printf_twod_array(char **array)
{
    int i = 0;
    while (array[i])
    {
        printf("%s\n", array[i]);
        i++;
    }
    printf("\n\n");
}

char    **concat_path(t_minishell *shell, char **dir_paths, char  *command)
{
    char    **new_dir_path = NULL;
    size_t     command_len;
    size_t     total_path_len;
    size_t     dir_path_len;
    size_t         num_dirs;
    size_t         i;
    size_t         j;
    size_t        k;

    command_len = ft_strlen(command);
    num_dirs = 0;
    i = 0;
    while (dir_paths[num_dirs] != NULL)
        num_dirs++;
    new_dir_path = (char **)malloc(num_dirs * sizeof(char *) + 1);
    if (!new_dir_path)
        exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
    while (i < num_dirs)
    {
        j = 0;
        dir_path_len = ft_strlen(dir_paths[i]);
        total_path_len = dir_path_len + command_len + 1;
        new_dir_path[i] = (char *)malloc(total_path_len * sizeof(char) + 1);
        if (!new_dir_path[i])
        {
            free_2darray(new_dir_path);
            exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
        }
        while (j < dir_path_len)
        {
            new_dir_path[i][j] = dir_paths[i][j];
            j++;
        }
        // printf_twod_array(new_dir_path);
        new_dir_path[i][j] = '/';
        k = 0;
        j++;
        while (j < total_path_len)
        {
            new_dir_path[i][j] = command[k];
            j++;
            k++;
        }
        new_dir_path[i][j] = '\0';
        i++;
    }
    new_dir_path[i] = NULL;
    return (new_dir_path);
}

char    **get_pathdirs(t_minishell *shell, t_process *process)
{
    // char            *pathname;
    t_environment   *current;
    char            **dir_paths = NULL;
    char            **new_dir_paths = NULL;
    
    current = shell->env_list;
    while (current != NULL)
    {
        if (ft_strcmp(current->env_var, "PATH") == 0)
        {
            // printf("the path: %s\n", current->value);
            dir_paths = ft_split(current->value, ':');
            if (!dir_paths)
                exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
            // printf_twod_array(dir_paths);
            break ;
        }
        current = current->next_env_var;
    }
    // printf("pro-commnd: %s\n", process->command_arguments[0]);
    new_dir_paths = concat_path(shell, dir_paths, process->command_arguments[0]);
    // printf_twod_array(new_dir_paths);
    return (new_dir_paths);
}

char    *get_path(t_minishell *shell, t_process *process)
{
    char    **path_dirs = NULL;
    char    *path = NULL;;
    int i;

    i = 0;
    path_dirs = get_pathdirs(shell, process);
    while (path_dirs[i] != NULL)
    {
        if (access(path_dirs[i], X_OK) == 0)
        {
            path = ft_strdup(path_dirs[i]);
            if (!path)
                exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
            break ;
        }
        i++;
    }
    return (path);
}


