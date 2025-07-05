/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:14:38 by wxi               #+#    #+#             */
/*   Updated: 2025/07/05 18:32:19 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "minishell.h"

void	free_2darray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_pipes2(int **pipes, int p_num)
{
	int	i;

	i = 0;
	while (i < p_num)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	pipes = NULL;
}

void	free_process(t_minishell *shell, t_process *current)
{
	if (shell->pipes)
		close_pipe_ends(shell, current);
	if (shell->env_list)
		ft_lstclear_env(&shell->env_list);
	ft_lstclear_process(&shell->process_list);
	if (shell->pipes)
		free_pipes(shell);
}

void	ft_clear_shell(t_minishell *shell)
{
	if (shell)
	{
		ft_lstclear_token(&shell->token_list);
		ft_lstclear_env(&shell->env_list);
		ft_lstclear_process(&shell->process_list);
		if (shell->input_str)
			free(shell->input_str);
		if (shell->pipes)
		{
			free_pipes(shell);
			shell->pipes = NULL;
		}
		shell = NULL;
	}
}