/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 10:02:02 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ls > temp.txt | grep txt < temp.txt | wc -l >> count.log

int redirections(t_process *process_lst)
{
    t_redirection *redir1;
    t_redirection *redir2;
    t_redirection *redir3;
    t_process     *current;
    

    current = process_lst;
    redir1 = new_redir_lst(STDIN_FILENO, OUTPUT, ft_strdup("temp.txt"));
    current->redirections = redir1;
    
    current = current->next_process;
    redir2 = new_redir_lst(STDIN_FILENO, OUTPUT, ft_strdup("temp.txt"));
    current->redirections = redir2;
    
    current = current->next_process;
    redir3 = new_redir_lst(STDIN_FILENO, OUTPUT, ft_strdup("count.log"));
    current->redirections = redir3;

    current = process_lst;
    while (current != NULL)
    {
        printf("redir file: %s\n", current->redirections->file);
        current = current->next_process;
    }
    
    return (1);
}