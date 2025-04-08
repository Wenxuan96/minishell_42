/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/08 19:01:08 by wxi              ###   ########.fr       */
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
		assign_fd(&shell);
		create_processes(&shell);
		print_fds(&shell);
	}
	ft_exit(&shell, NULL);
	return (0);
}
