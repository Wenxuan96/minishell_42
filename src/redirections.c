/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/21 13:35:25 by tignatov         ###   ########.fr       */
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
    redir1 = new_redir_lst(current->output_fd, OUTPUT, ft_strdup("temp.txt"));
    current->redirections = redir1;
    
    
    current = current->next_process;
    redir2 = new_redir_lst(current->input_fd, INPUT, ft_strdup("temp.txt"));
    current->redirections = redir2;
    
    current = current->next_process;
    redir3 = new_redir_lst(current->output_fd, OUTPUT_APPEND, ft_strdup("count.log"));
    current->redirections = redir3;

    current = process_lst;
    while (current != NULL)
    {
        printf("redir file: %s\n", current->redirections->file);
        current = current->next_process;
    }
    
    return (1);
}

int handle_redirection(t_process *process)
{
    t_process     *current;
    t_redirection *curr_redir;
    
    current = process;
    curr_redir = current->redirections;
    while (curr_redir != NULL)
    {
        if (curr_redir->type == OUTPUT)
            current->output_fd = open(curr_redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        else if (curr_redir->type == INPUT)
            current->input_fd = open(curr_redir->file, O_RDONLY);
        else if (curr_redir->type == OUTPUT_APPEND)
            current->output_fd = open(curr_redir->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
        curr_redir = curr_redir->next_redir;
    }
    return (1);
}