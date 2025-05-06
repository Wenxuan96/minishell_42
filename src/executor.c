/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:15:50 by tanja             #+#    #+#             */
/*   Updated: 2025/05/05 15:51:03 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

#include <stdio.h>

int    execute_builtin(t_process *process, t_minishell *shell)
{
    t_process   *current;

    current = process;
    if (handle_redirection(current) == 0)
        return (close_pipe_ends(shell, current), 0);
    
    if (dup2(current->input_fd, STDIN_FILENO) == -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
    // else
    // {
    //     if (current->input_fd != STDIN_FILENO)
    //         close (current->input_fd);
    // }
    // if (current->input_fd != STDIN_FILENO)
    //     close(current->input_fd);
        
    if (dup2(current->output_fd, STDOUT_FILENO) ==  -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
    // else
    // {
    //     if (current->output_fd != STDOUT_FILENO)
    //         close (current->output_fd);
    // }
    
    // printf("input fd: %i\n",current->input_fd);
	// printf("output fd: %i\n",current->output_fd);
    // if (current->output_fd != STDOUT_FILENO)
    // {
    //     dprintf(2, "executing %s\n", current->command_arguments[0]);
    //     close(current->output_fd);
    // }
    close_pipe_ends(shell, current);
    current->builtin->function(current, shell);
    return (1);
}

int    execute_outside_cmd(t_process *process, t_minishell *shell)
{
    t_process   *current;
    char		*path;
	char		**env_vars;
    
    current = process;
    if (handle_redirection(current) == 0)
        return (close_pipe_ends(shell, current), 0);
    if (dup2(current->input_fd, STDIN_FILENO) == -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
    if (current->input_fd != STDIN_FILENO)
        close(current->input_fd);
    if (dup2(current->output_fd, STDOUT_FILENO) ==  -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
    if (current->output_fd != STDOUT_FILENO)
        close(current->output_fd);
    close_pipe_ends(shell, current);
    path = get_path(shell, process);
    env_vars = execve_get_envvars(current);
    // printf_twod(env_vars);
    execve(path, current->command_arguments, env_vars);
    return (1);
}
