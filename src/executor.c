/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:15:50 by tanja             #+#    #+#             */
/*   Updated: 2025/04/28 16:42:25 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int    execute_builtin(t_process *process, t_minishell *shell)
{
    t_process   *current;

    (void)shell;
    current = process;
    if (handle_redirection(current) == 0)
        return (close_pipe_ends(shell, current), 0);
    if (dup2(current->input_fd, STDIN_FILENO) == -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
    if (dup2(current->output_fd, STDOUT_FILENO) ==  -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
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
    if (dup2(current->output_fd, STDOUT_FILENO) ==  -1)
    {
        display_shell_error("dup2 failed", EXEC_FAILURE);
        return (close_pipe_ends(shell, current), 0);
    }
    close_pipe_ends(shell, current);
    path = get_path(shell, process);
    env_vars = execve_get_envvars(current);
    // printf_twod(env_vars);
    execve(path, current->command_arguments, env_vars);
    return (1);
}
