/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:28:14 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/24 17:44:21 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_shell_error(char *msg, int exit_status)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
    g_exit_status = exit_status;
}

void	error_exit(t_minishell *shell, char *error_msg)
{
	int	i;

	i = 0;
	if (!shell->input_status && error_msg)
		ft_printf("%s\n", error_msg);
	else if (error_msg)
		ft_printf("Error: %s.\n", error_msg);
	else if (!shell && !error_msg)
		exit(MS_EXIT_SUCCESS);
	else
	{
		ft_lstclear_token(&shell->token_list);
		ft_lstclear_env(&shell->env_list);
		ft_lstclear_process(&shell->process_list);
		if (shell->input_str)
			free (shell->input_str);
		if (shell->pipes)
			free_pipes(shell);
		shell = NULL;
	}
	exit(MS_EXIT_SUCCESS);
}