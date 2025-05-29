/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/29 14:33:07 by tignatov         ###   ########.fr       */
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
	t_process *p;
	// t_environment	*env_list;
	// t_process		*current;
	// t_process	*head;
	(void)argc;
	(void)argv;
	init_shell(&shell);
	setup_signals(0);
	create_env_lst(&shell.env_list, envp);
	while (1)
	{
		shell.input_status = read_input(argc, &shell);
		if (shell.input_status != EXEC_SUCCESS)
			display_shell_error2(&shell, "lexer failed", EXEC_FAILURE);
		p = shell.process_list;
		while (p)
		{
			p->input_fd = STDIN_FILENO;
			p->output_fd = STDOUT_FILENO;
			p = p->next_process;
		}
		if (shell.input_status == 2) /* When receiving empty str as input */
			continue; /* skip all functions below, rerun while loop and awaits for new input */
		create_pipes(&shell);
		assign_fd(&shell);
		// print_fds(&shell);
		create_processes(&shell);
		p = shell.process_list;
		while (p)
		{
			p->input_fd = STDIN_FILENO;
			p->output_fd = STDOUT_FILENO;
			p = p->next_process;
		}
		// ft_lstclear_token(&shell.token_list);
		ft_lstclear_process(&shell.process_list);
		// ft_lstclear_env(&shell.env_list);
		if (shell.pipes)
			free_pipes(&shell);
	}
	ft_exit(&shell, NULL);
	return (0);
}
