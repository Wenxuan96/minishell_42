/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/09 19:41:46 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell		shell;
	t_environment	*env_list;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	while (1)
	{
		shell.input_status = read_input(argc, argv, &shell);
		if (shell.input_status == MS_EXIT_FAILURE) /*When ctrl+D is pressed*/
			break;/* Break the loop, clean memory and exit */
		if (shell.input_status == 2) /* When receiving empty str as input */
			continue; /* skip all functions below, rerun while loop and awaits for new input */
	create_env_lst(&env_list, envp);
	create_pipes(&shell);
	redirections(shell.process_list);
	assign_fd(&shell);
	create_processes(&shell);
	print_fds(&shell);
	}
	ft_exit(&shell, NULL);
	return (0);
}
