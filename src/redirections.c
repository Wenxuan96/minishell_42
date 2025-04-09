/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:32:07 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/09 17:43:55 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ls > temp.txt | grep txt < temp.txt | wc -l >> count.log

int redirections(t_process *process)
{
    t_redirection *redir_lst;
    
    redir_lst = NULL;
    new_redir_lst(process->output_fd, OUTPUT, ft_strdup("temp.txt"));
    
}