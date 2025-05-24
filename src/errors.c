/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:28:14 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/24 14:34:22 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_shell_error(t_process *process, char *msg, int exit_status)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
    process->exit_status = exit_status;
}

void    display_shell_error2(t_minishell *shell, char *msg, int exit_status)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
    shell->exit_status = exit_status;
}

void	free_everything(t_minishell *shell)
{
	// ft_lstclear_token(&shell->token_list);
	ft_lstclear_env(&shell->env_list);
	ft_lstclear_process(&shell->process_list);
	if (shell->input_str)
		free(shell->input_str);
	if (shell->pipes)
		free_pipes(shell);
	// exit(g_exit_status);
}

void    exit_with_error(t_minishell *shell, char *msg, int exit_status)
{
    display_shell_error2(shell, msg, exit_status);
    free_everything(shell);
}
