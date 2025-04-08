/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/08 16:38:54 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Step 1: read from stdinput and save the input
Signal is needed to continue reading user input
if signal is received, read and malloc stdin
*/

void archive_input(char	*input_str, t_minishell *shell)
{
	
}

int	read_input(int argc, char **argv, t_minishell *shell)
{
	int	init;
	(void)argv;

	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str)
		return (0);
	if (shell->input_str[0] == '\0')
		return (2);
	archive_input(shell->input_str, shell);
	return(1);
}