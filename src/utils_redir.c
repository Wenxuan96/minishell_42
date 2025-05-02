/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:05:22 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/02 15:52:02 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_redirection    *new_redir_lst(t_redir_type type, char *file)
{
    t_redirection   *redir;
    redir = malloc(sizeof(t_redirection));
    // redir->fd = fd;
    redir->type = type;
    redir->file = file;
    redir->next_redir = NULL;
    return (redir);
}

void    redir_lst_add_back(t_redirection *new_redir, t_redirection **redir_lst)
{
    t_redirection *current;

    if (*redir_lst == NULL)
    {
        *redir_lst = new_redir;
        return ;
    }
    current = *redir_lst;
    while (current->next_redir != NULL)
        current = current->next_redir;
    current->next_redir = new_redir;
}
