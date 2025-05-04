/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/05/04 14:36:03 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prt_tokenlst(t_minishell *shell)
{
	t_token *current;

	current = shell->token_list;
	if (!current)
		return ;
	ft_printf("current tokens are:");
	while (current != NULL)
	{
		ft_printf(" [%s]", current->token_val);
		current = current->next_token;
	}
	ft_printf(".\n");
}

int	read_input(int argc, t_minishell *shell)
{
	int	init;
	int	i;
	
	i = 0;
	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	free_tokenlst(shell);
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str) /*When ctrl+D is pressed, break the loop, clean memory and exit*/
		ft_exit(shell, "exit");
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	tokenize_input(shell);
	init_processlst(shell);
	// prt_tokenlst(shell);
	return(EXEC_SUCCESS);
}
