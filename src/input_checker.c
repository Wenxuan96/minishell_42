/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/21 18:25:01 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Step 1: read from stdinput and save the input
Signal is needed to continue reading user input
if signal is received, read and malloc stdin
*/

// static void prt_input(char **input_arr)
// {
// 	int	i;
	
// 	i = 0;
// 	while (input_arr[i])
// 		ft_printf("current splitted input is: %s\n", input_arr[i++]);
// }

void prt_tokenlst(t_minishell *shell)
{
	t_token *current;

	current = shell->token_list;
	while (current != NULL)
	{
		ft_printf("current token is: %s, it is a %i token type\n", current->token_val, current->type);
		current = current->next_token;
	}
}

void free_tokenlst(t_minishell *shell)
{
	t_token	*current;

	if (!shell->token_list)
		return ;
	while (shell->token_list)
	{
		current = shell->token_list->next_token;
		free(shell->token_list->token_val);
		free(shell->token_list);
		shell->token_list = current;
	}
	shell->token_list = NULL;
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
	if (!shell->input_str)
	{ /*When ctrl+D is pressed, break the loop, clean memory and exit*/
		ft_exit(shell, "exit");
		return(MS_EXIT_SUCCESS);
	}
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	tokenize_input(shell);
	prt_tokenlst(shell);
	return(MS_EXIT_SUCCESS);
}
