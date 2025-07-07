/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 15:09:06 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(t_process *process, t_minishell *shell)
{
	t_process		*current;
	t_redirection	*curr_redir;
	int				pipe_fd[2];
	char			*input_line;
	char			*heredoc_buff;
	char			*temp;
	t_token			*cmd_holder;

	current = process;
	heredoc_buff = NULL;
	(void)shell;
	curr_redir = current->redirections; 
	while (curr_redir != NULL)
	{
		if (curr_redir->type == OUTPUT)
		{
			current->output_fd = open(curr_redir->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (current->output_fd == -1)
				return (display_shell_error(current, "open failed",
						EXEC_FAILURE), 0);
			if (curr_redir->next_redir != NULL)
				close(current->output_fd);
		}
		else if (curr_redir->type == INPUT)
		{
			current->input_fd = open(curr_redir->file, O_RDONLY);
			if (current->input_fd == -1)
				return (display_shell_error(current, "open failed",
						EXEC_FAILURE), 0);
			if (curr_redir->next_redir != NULL
				&& (curr_redir->next_redir->type == INPUT))
				close(current->input_fd);
		}
		else if (curr_redir->type == OUTPUT_APPEND)
		{
			current->output_fd = open(curr_redir->file,
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (current->output_fd == -1)
				return (display_shell_error(current, "open failed",
						EXEC_FAILURE), 0);
			if (curr_redir->next_redir != NULL
				&& (curr_redir->next_redir->type == OUTPUT
					|| curr_redir->next_redir->type == OUTPUT_APPEND))
				close(current->output_fd);
		}
		else if (curr_redir->type == HEREDOC)
		{
			setup_signals_heredoc();
			pipe(pipe_fd);
			input_line = readline("> ");
			if (!input_line || g_exit_status == 130)
			{
				free(input_line);
				free(heredoc_buff);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				return (0);
			}
			while (input_line && ft_strcmp(input_line, curr_redir->file) != 0)
			{
				if (heredoc_buff == NULL)
					heredoc_buff = ft_strdup(input_line);
				else
				{
					temp = heredoc_buff;
					heredoc_buff = ft_strjoin_heredoc(temp, input_line);
					free(temp);
				}
				free(input_line);
				input_line = readline("> ");
			}
			if (shell->heredoc_inquote != true && heredoc_buff != NULL)
			{
				cmd_holder = new_token_lst(heredoc_buff);
				heredoc_buff = def_expansion(cmd_holder, shell);
				free(cmd_holder);
			}
			if (current->command_arguments[0] == NULL)
			{
				// write(1, heredoc_buff, ft_strlen(heredoc_buff));
				// write(1, "\n", 1);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			else
			{
				if (!heredoc_buff)
				{
					write(pipe_fd[1], "", 1);
					current->input_fd = pipe_fd[0];
					close(pipe_fd[1]);
				}
        		else
				{
					write(pipe_fd[1], heredoc_buff, ft_strlen(heredoc_buff));
					write(pipe_fd[1], "\n", 1);
					current->input_fd = pipe_fd[0];
					close(pipe_fd[1]);
				}
			}
			free(heredoc_buff);
		}
		curr_redir = curr_redir->next_redir;
	}
	return (1);
}
