/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/09 14:11:42 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "minishell.h"

void	print_env(t_environment *env_list)
{
	while (env_list)
	{
		printf("%s=", env_list->env_var);
		printf("%s\n", env_list->value);
		env_list = env_list->next_env_var;
	}
}

void	set_process(t_minishell	shell, t_process **p)
{
	*p = shell.process_list;
	while (*p)
	{
		(*p)->input_fd = STDIN_FILENO;
		(*p)->output_fd = STDOUT_FILENO;
		*p = (*p)->next_process;
	}
}

void	run_shell(int argc, t_minishell	shell, t_process *p)
{
	while (1)
	{
		shell.exit_status = read_input(argc, &shell);
		if (shell.exit_status == EXEC_FAILURE)
			display_shell_error2(&shell, "lexer failed.", EXEC_FAILURE);
		if (shell.exit_status == 2)
		{
			ft_clear_shell(&shell);
			continue ;
		}
		if (shell.exit_status == CMD_NOTFOUND)
		{
			display_shell_error2(&shell, "Command '' not found.", CMD_NOTFOUND);
			continue ;
		}
		set_process(shell, &p);
		create_pipes(&shell);
		assign_fd(&shell);
		create_processes(&shell);
		set_process(shell, &p);
		ft_lstclear_process(&shell.process_list);
		if (shell.pipes)
			free_pipes(&shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_process	*p;

	(void)argc;
	(void)argv;
	p = NULL;
	init_shell(&shell);
	setup_signals(0);
	create_env_lst(&shell.env_list, envp);
	run_shell(argc, shell, p);
	ft_exit(&shell, NULL);
	return (EXEC_SUCCESS);
}
