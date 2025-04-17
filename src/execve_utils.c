/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:42 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/17 17:24:21 by tignatov         ###   ########.fr       */
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

char    **concat_path(char **dir_paths, char  *command)
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
    while (i < num_dirs)
    {
        j = 0;
        dir_path_len = ft_strlen(dir_paths[i]);
        total_path_len = dir_path_len + command_len + 1;
        new_dir_path[i] = (char *)malloc(total_path_len * sizeof(char) + 1);
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

char    **get_pathdirs(t_process *process)
{
    // char            *pathname;
    t_environment   *current;
    char            **dir_paths = NULL;
    char            **new_dir_paths = NULL;
    
    current = process->env_vars;
    while (current != NULL)
    {
        if (ft_strcmp(current->env_var, "PATH") == 0)
        {
            // printf("the path: %s\n", current->value);
            dir_paths = ft_split(current->value, ':');
            // printf_twod_array(dir_paths);
            break ;
        }
        current = current->next_env_var;
    }
    // printf("pro-commnd: %s\n", process->command_arguments[0]);
    new_dir_paths = concat_path(dir_paths, process->command_arguments[0]);
    // printf_twod_array(new_dir_paths);
    return (new_dir_paths);
}

char    *get_path(t_process *process)
{
    char    **path_dirs = NULL;
    char    *path = NULL;;
    int i;

    i = 0;
    path_dirs = get_pathdirs(process);
    while (path_dirs[i] != NULL)
    {
        if (access(path_dirs[i], X_OK) == 0)
        {
            path = ft_strdup(path_dirs[i]);
            break ;
        }
        i++;
    }
    return (path);
}


