/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/17 15:47:13 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins//builtins.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell		shell;
// 	t_environment	*env_list;
// 	t_process		*current;

// 	(void)argc;
// 	(void)argv;
// 	init_shell(&shell);
// 	create_env_lst(&env_list, envp);
// 	while (1)
// 	{
// 		shell.input_status = read_input(argc, &shell);
// 		if (shell.input_status == 2) /* When receiving empty str as input */
// 			continue; /* skip all functions below, rerun while loop and awaits for new input */
// 		create_pipes(&shell);
// 		redirections(shell.process_list);
// 		assign_fd(&shell);
// 		create_processes(&shell);
// 		assign_builtin(shell.process_list);
// 		current = shell.process_list;
// 		printf("builtin : %i\n", current->is_builtin);
// 		if (current->is_builtin == 1)
// 		{
// 			printf("builtin type : %i\n", current->builtin->type);
// 			shell.process_list->builtin->function(current);
// 		}
// 	}
// 	print_fds(&shell);
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
	create_env_lst(&shell.env_list, envp);
	///redirectios here<
	create_pipes(&shell);
	// redirections(shell.process_list);
	assign_fd(&shell);
	create_processes(&shell);
	// head = shell.process_list;
	// assign_builtin(shell.process_list, ENV, env_builtin);
	// shell.process_list->builtin->function(shell.process_list);

	// assign_builtin(shell.process_list->next_process, UNSET, unset_builtin);
	// shell.process_list->next_process->builtin->function(shell.process_list->next_process);
	
	// prt_env_lst(&shell.process_list->next_process->env_vars);
	// current = shell.process_list;
	// printf("builtin : %i\n", current->is_builtin);
	// if (current->is_builtin == 1)
	// {
	// 	printf("builtin type : %i\n", current->builtin->type);
	// 	shell.process_list->builtin->function(current);
	// }
	return (0);
}
