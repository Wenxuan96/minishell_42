/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:15:50 by tanja             #+#    #+#             */
/*   Updated: 2025/04/26 19:55:18 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void    execute_builtin(t_process *process, t_minishell *shell)
{
    t_process   *current;

    (void)shell;
    current = process;
    handle_redirection(current);
    dup2(current->input_fd, STDIN_FILENO);
    dup2(current->output_fd, STDOUT_FILENO);
    current->builtin->function(current, shell);
}
