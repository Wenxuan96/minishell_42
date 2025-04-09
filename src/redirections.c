/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/09 17:52:36 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ls > temp.txt | grep txt < temp.txt | wc -l >> count.log

int redirections(t_process *process)
{
    t_redirection *redir1;
    t_redirection *redir2;
    t_redirection *redir3;
    

    redir1 = new_redir_lst(process->output_fd, OUTPUT, ft_strdup("temp.txt"));
    redir2 = new_redir_lst(process->output_fd, OUTPUT, ft_strdup("temp.txt"));
    redir3 = new_redir_lst(process->output_fd, OUTPUT, ft_strdup("count.log"));
    
}