/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:54 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 14:23:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cd_builtin(t_process *process)
{
	char    *path;

    path = process->command_arguments[1];
    chdir(path); //feed th efunciton env vars// update the vars
}
