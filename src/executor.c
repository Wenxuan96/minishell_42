/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:15:50 by tanja             #+#    #+#             */
/*   Updated: 2025/05/08 16:31:14 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int    execute_builtin(t_process *process, t_minishell *shell)
{
    t_process   *current;

    current = process;
    if (current->redirections != NULL)
    {
        // write(2, "here\n", 5);
        // printf("redir type: %u, redir file: %s\n", current->redirections->type, current->redirections->file);
        if (handle_redirection(current) == 0)
            return (close_pipe_ends(shell, current), 0);
        // printf("read end before: %i\n", current->input_fd);
		// printf("write end before: %i\n\n", current->output_fd);
        // handle_redirection(current);
        // printf("read end: %i\n", current->input_fd);
		// printf("write end: %i\n\n", current->output_fd);
        
    }
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
    dprintf(2, "outout fd: %i\n", current->output_fd);
    if (current->output_fd != STDOUT_FILENO)
        close (current->output_fd);
    
    // printf("input fd: %i\n",current->input_fd);
	// printf("output fd: %i\n",current->output_fd);
    // if (current->output_fd != STDOUT_FILENO)
    // {
    //     dprintf(2, "executing %s\n", current->command_arguments[0]);
    //     close(current->output_fd);
    // }
    if (shell->pipes)
        close_pipe_ends(shell, current);
    current->builtin->function(current, shell);
    // ft_lstclear_env(&shell->env_list);
    // ft_lstclear_process(&shell->process_list);
    // free_pipes(shell);
    // ft_lstclear_token(&shell->token_list);
    // free(shell->input_str);
    return (1);
}

int    execute_outside_cmd(t_process *process, t_minishell *shell)
{
    t_process   *current;
    char		*path;
	char		**env_vars;
    
    current = process;
    if (current->redirections != NULL)
    {
        if (handle_redirection(current) == 0)
            return (close_pipe_ends(shell, current), 0);
    }
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
    if (shell->pipes)
        close_pipe_ends(shell, current);
    path = get_path(shell, process);
    env_vars = execve_get_envvars(current);
    // printf_twod(env_vars);
    // ft_lstclear_env(&shell->env_list);
    // ft_lstclear_token(&shell->token_list);
    // free_pipes(shell);
    // free(shell->input_str);
    execve(path, current->command_arguments, env_vars);
    // ft_lstclear_process(&shell->process_list);
    return (1);
}
