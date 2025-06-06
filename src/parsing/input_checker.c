/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/06/06 17:35:31 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_tokenlst(t_minishell *shell)
{
	t_token	*current;

	current = shell->token_list;
	if (!current)
		return ;
	ft_printf("current tokens are:");
	while (current != NULL)
	{
		ft_printf(" [%s: %s]", current->token_val, current->type);
		current = current->next_token;
	}
	ft_printf(".\n");
}

int	read_input(int argc, t_minishell *shell)
{
	int	init;
	// int	i;
	
	// i = 0;
	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	shell->input_str = readline("minishell$ ");
	// write(2, "read_line\n", 11);
	if (!shell->input_str) /*When ctrl+D is pressed, break the loop, clean memory and exit*/
		ft_exit(shell, "exit");
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	if (!tokenize_input(shell))
		return (0);
	if (init_processlst(shell) == 0)
	{
		free(shell->input_str);
		free(shell->token_list);
		free(shell);
		shell = NULL;
		exit(g_exit_status);
	}
	// prt_tokenlst(shell);
	free_tokenlst(shell);
	free(shell->input_str);
	return(EXEC_SUCCESS);
}
