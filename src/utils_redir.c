/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:05:22 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/09 17:42:59 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection    *new_redir_lst(int fd, t_redir_type type, char *file)
{
    t_redirection   *redir;
    redir = malloc(sizeof(t_redirection));
    redir->fd = -1;
    redir->type = NONE;
    redir->file = NULL;
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
