/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:53:06 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/14 15:07:40 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strjoin_heredoc(char *input_line, char **heredoc_buff)
{
	char	*temp;

	temp = *heredoc_buff;
	*heredoc_buff = ft_strjoin_heredoc(temp, input_line);
	free(temp);
}

char	*read_into_heredoc(t_redirection *curr_redir, int *pipe_fd)
{
	char	*input_line;
	char	*heredoc_buff;

	heredoc_buff = NULL;
	rl_event_hook = force_sigint;
	while (1)
	{
		g_exit_status = 0;
		setup_signals_heredoc();
		input_line = readline("> ");
		if (!input_line || g_exit_status == 130)
			return (free_heredoc(input_line, heredoc_buff, pipe_fd), NULL);
		if (ft_strcmp(input_line, curr_redir->file) == 0)
		{
			free(input_line);
			break ;
		}
		if (heredoc_buff == NULL)
			heredoc_buff = ft_strdup(input_line);
		else
			strjoin_heredoc(input_line, &heredoc_buff);
		free(input_line);
	}
	return (heredoc_buff);
}

char	*expand_heredoc(char *heredoc_buff, t_minishell *shell)
{
	t_token	*cmd_holder;
	char	*expanded;

	cmd_holder = new_token_lst(heredoc_buff);
	expanded = def_expansion(cmd_holder, shell);
	free(cmd_holder->token_val);
	free(cmd_holder);
	free(heredoc_buff);
	return (expanded);
}

void	write_heredoc(t_process *current, char *heredoc_buff, int *pipe_fd)
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

int	handle_heredoc(t_process *current, t_redirection *curr_redir,
		t_minishell *shell)
{
	int		pipe_fd[2];
	char	*heredoc_buff;

	heredoc_buff = NULL;
	if (!setup_pipes(pipe_fd))
		return (display_shell_error(current, "pipe failed", EXEC_FAILURE), 0);
	heredoc_buff = read_into_heredoc(curr_redir, pipe_fd);
	if (!heredoc_buff || g_exit_status == 130)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (0);
	}
	if (shell->heredoc_inquote != true && heredoc_buff != NULL)
		heredoc_buff = expand_heredoc(heredoc_buff, shell);
	if (current->command_arguments[0] == NULL)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	else
		write_heredoc(current, heredoc_buff, pipe_fd);
	free(heredoc_buff);
	return (1);
}
