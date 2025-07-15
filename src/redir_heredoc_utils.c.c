/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils.c.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:53:06 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/15 16:46:51 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_heredoc(char *input_line, char *heredoc_buff, int *pipe_fd)
{
	free(input_line);
	if (heredoc_buff)
		free(heredoc_buff);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

int	force_sigint(void)
{
	return (0);
}

int	setup_pipes(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		return (0);
	return (1);
}
