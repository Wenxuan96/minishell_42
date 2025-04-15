/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:26:37 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/15 14:56:04 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	free_pipes(t_minishell *shell);

void	ft_clean_exit(t_minishell *shell)
{
	ft_lstclear_token(&shell->token_list);
	ft_lstclear_env(&shell->env_list);
	ft_lstclear_process(&shell->process_list);
	if (shell->input_str)
		free (shell->input_str);
	if (shell->pipes)
		free_pipes(shell);
	shell = NULL;
	exit(0);
}
void	free_pipes(t_minishell *shell)
{
	int	i;
	
	i = 0;
	while (i < shell->num_processes - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
}