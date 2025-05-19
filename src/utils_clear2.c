/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clear2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:25:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/19 13:33:48 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./builtins/builtins.h"

void ft_exit(t_minishell *shell, char *error_msg)
{
    if (error_msg)
        ft_printf("%s\n", error_msg);
    
    if (shell) {
        // ft_lstclear_token(&shell->token_list);
        ft_lstclear_env(&shell->env_list);
        ft_lstclear_process(&shell->process_list);
        
        // if (shell->input_str)
        //     free(shell->input_str);
        
        if (shell->pipes) {
            free_pipes(shell);
            shell->pipes = NULL;
        }
    }
    exit(EXEC_SUCCESS);
}

void    free_process(t_minishell *shell, t_process *current)
{
    if (shell->pipes)
        close_pipe_ends(shell, current);
    if (shell->env_list)
        ft_lstclear_env(&shell->env_list);
    ft_lstclear_process(&shell->process_list); 
    if (shell->pipes)
        free_pipes(shell);
    // ft_lstclear_token(&shell->token_list);
    // free(shell->input_str);
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