/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/09 20:47:43 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Step 1: read from stdinput and save the input
Signal is needed to continue reading user input
if signal is received, read and malloc stdin
*/

int		sys_sep_checker(t_minishell *shell, char c)
{
	int	i;
	
	i = 0;
	while (shell->system_separators[i])
	{
		if (c == shell->system_separators[i])
			return (1);
		i++;
	}
	return (0);
}

char	*split_input_str(t_minishell *shell)
{
	char	**separator_arr;
	int		i;

	i = 0;
	separator_arr = NULL;
	while (shell->input_str[i])
	{
		if (sys_sep_checker(shell->input_str[i], shell))
		{
			
		}
	}
}

t_token	*init_token(t_minishell *shell)
{
	t_token new_token;

}

int	read_input(int argc, char **argv, t_minishell *shell)
{
	int	init;
	(void)argv;
	int	i;

	i = 0;
	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str) /*When ctrl+D is pressed, break the loop, clean memory and exit */
		return (MS_EXIT_FAILURE);
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	return(MS_EXIT_SUCCESS);
}
