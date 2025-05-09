/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/09 08:44:58 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ls > temp.txt | grep txt < temp.txt | wc -l >> count.log

// int redirections(t_process *process_lst)
// {
//     t_redirection *redir1;
//     t_redirection *redir2;
//     t_redirection *redir3;
//     t_process     *current;
    

//     current = process_lst;
//     redir1 = new_redir_lst(OUTPUT, ft_strdup("temp.txt"));
//     current->redirections = redir1;
    
    
//     current = current->next_process;
//     redir2 = new_redir_lst(INPUT, ft_strdup("temp.txt"));
//     current->redirections = redir2;
    
//     current = current->next_process;
//     redir3 = new_redir_lst(OUTPUT_APPEND, ft_strdup("count.log"));
//     current->redirections = redir3;

//     current = process_lst;
//     // while (current != NULL)
//     // {
//     //     printf("redir file: %s\n", current->redirections->file);
//     //     current = current->next_process;
//     // }
    
//     return (1);
// }


//echo hello > test5.txt | grep hello < test5.txt | wc -c > textresult.txt

int handle_redirection(t_process *process)
{
    t_process     *current;
    t_redirection *curr_redir;
    
    current = process;
    curr_redir = current->redirections;
    while (curr_redir != NULL)
    {
        if (curr_redir->type == OUTPUT)
        {
            // if (current->output_fd < 0)
            //     close(current->output_fd);
            current->output_fd = open(curr_redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            // dprintf(2, "OUTPUT to %s %i\n", curr_redir->file, current->output_fd);
            if (current->output_fd == -1)
                return (display_shell_error("open failed", EXEC_FAILURE), 0);
        } 
        else if (curr_redir->type == INPUT)
        {
            current->input_fd = open(curr_redir->file, O_RDONLY);
            // printf("redir input fd: %i\n",current->input_fd);
            // printf("input fd: %i\n",current->output_fd);
            if (current->input_fd == -1)
                return (display_shell_error("open failed", EXEC_FAILURE), 0);
        }
        else if (curr_redir->type == OUTPUT_APPEND)
        {
            current->output_fd = open(curr_redir->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
            // printf("output fd: %i\n",current->output_fd);
            if (current->output_fd == -1)
                return (display_shell_error("open failed", EXEC_FAILURE), 0);
        }
        // printf("input fd: %i\n",current->output_fd);
        // printf("output fd: %i\n",current->output_fd);
        curr_redir = curr_redir->next_redir;
    }
    return (1);
}
