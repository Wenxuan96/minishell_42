/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/03 19:03:04 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *shell, char *error_msg)
{
	if (!shell)
		ft_printf("Error: %s.\n", error_msg);
	else
	{
		ft_lstclear_token(&shell->token_list);
		ft_lstclear_env(&shell->env_list);
		ft_lstclear_process(&shell->process_list);
	}
	exit(EXIT_SUCCESS);
}

//Step 1: read from stdinput and save the input
//Signal is needed to continue reading user input
//if signal is received, read and malloc stdin
int	read_input(int argc, char **argv, t_minishell *shell)
{
	int	init;
	(void)argv;

	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	ft_printf("n: %d", argc);
	return(0);
}