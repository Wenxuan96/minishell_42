/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/04 16:06:10 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell		shell;

// 	(void)argc;
// 	(void)argv;
// 	init_shell(&shell);
// 	create_env_lst(&shell.env_list, envp);
// 	while (1)
// 	{
// 		shell.input_status = read_input(argc, &shell);
// 		if (shell.input_status == 2) /* When receiving empty str as input */
// 			continue; /* skip all functions below, rerun while loop and awaits for new input */
// 	}
// 	ft_exit(&shell, NULL); //   <--- segfaulting
// 	return (0);
// }


int	main(int argc, char **argv, char **envp)
{
	t_minishell		shell;
	// t_environment	*env_list;
	// t_process		*current;
	// t_process	*head;
	(void)argc;
	(void)argv;
	init_shell(&shell);
	setup_signals();
	create_env_lst(&shell.env_list, envp);
	while (1)
	{
		shell.input_status = read_input(argc, &shell);
		if (shell.input_status == 2) /* When receiving empty str as input */
			continue; /* skip all functions below, rerun while loop and awaits for new input */
		create_pipes(&shell);
		assign_fd(&shell);
		// print_fds(&shell);
		create_processes(&shell);
		free_everything(&shell);
	}
	// ft_exit(&shell, NULL); //   <--- segfaulting
	return (0);
}
