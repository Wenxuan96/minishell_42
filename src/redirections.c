/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/14 16:00:03 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output(t_process *current, t_redirection *curr_redir)
{
	if (current->output_fd != -1)
		close(current->output_fd);
	current->output_fd = open(curr_redir->file, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (current->output_fd == -1)
		return (display_shell_error(current, "open failed", EXEC_FAILURE), 0);
	return (1);
}

int	handle_input(t_process *current, t_redirection *curr_redir)
{
	if (current->input_fd != -1)
		close(current->input_fd);
	current->input_fd = open(curr_redir->file, O_RDONLY);
	if (current->input_fd == -1)
		return (display_shell_error(current, "open failed", EXEC_FAILURE), 0);
	return (1);
}

int	handle_append(t_process *current, t_redirection *curr_redir)
{
	if (current->output_fd != -1)
		close(current->output_fd);
	current->output_fd = open(curr_redir->file, O_WRONLY | O_CREAT | O_APPEND,
			0666);
	if (current->output_fd == -1)
		return (display_shell_error(current, "open failed", EXEC_FAILURE), 0);
	return (1);
}

int	handle_redirection(t_process *process, t_minishell *shell)
{
	t_redirection	*curr_redir;

	(void)shell;
	curr_redir = process->redirections;
	while (curr_redir != NULL)
	{
		if (curr_redir->type == OUTPUT && !handle_output(process, curr_redir))
			return (0);
		else if (curr_redir->type == INPUT && !handle_input(process,
				curr_redir))
			return (0);
		else if (curr_redir->type == OUTPUT_APPEND && !handle_append(process,
				curr_redir))
			return (0);
		curr_redir = curr_redir->next_redir;
	}
	return (1);
}
