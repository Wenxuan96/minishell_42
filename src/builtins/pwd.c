/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:07:55 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 11:44:14 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int pwd_builtin(t_process *process)
{
    // char *getcwd(char *cwdbuf, size_t size);
    char    *path_buffer;
    
    path_buffer = getcwd(NULL, 0);
    write(process->output_fd, path_buffer, ft_strlen(path_buffer));
    write(process->output_fd, "\n", 1);
    write(STDOUT_FILENO, path_buffer, ft_strlen(path_buffer));
    write(STDOUT_FILENO, "\n", 1);
    return (1);
}
