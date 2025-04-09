/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:00:12 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/09 16:04:27 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->input_str = "\0";
	shell->input_archive = NULL;
	shell->token_list = NULL;
	shell->process_list = NULL;
	shell->num_processes = 0;
	shell->input_status = -1;
	shell->env_list = NULL;
	shell->pipes= NULL;
}

