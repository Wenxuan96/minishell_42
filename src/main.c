/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/03 16:14:24 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->input_str = "\0";
	shell->token_list = NULL;
	shell->process_list = NULL;
	shell->num_processes = 0;
	shell->env_list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_minishell		shell;
	t_environment	*env_list;

	init_shell(&shell);	
	create_env_lst(&env_list, envp);
	//Step 1: read from stdinput and save the input
	// create_pipes(&shell);
	// create_processes(&shell);
	pause();
}
