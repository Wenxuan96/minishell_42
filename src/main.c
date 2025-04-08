/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/08 13:02:01 by tignatov         ###   ########.fr       */
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
	shell->pipes= NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		shell;
	t_environment	*env_list;

	(void)argc;
	(void)argv;
	init_shell(&shell);	
	create_env_lst(&env_list, envp);
	// read_input(argc, argv, &shell);
	create_pipes(&shell);
	assign_fd(&shell);
	create_processes(&shell);
	print_fds(&shell);
	// pause();
}
