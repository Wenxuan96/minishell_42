/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/15 15:02:50 by wxi              ###   ########.fr       */
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

int	read_input(int argc, t_minishell *shell)
{
	int	init;
	int	i;
	t_process ms_process;

	i = 0;
	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str) /*When ctrl+D is pressed, break the loop, clean memory and exit*/
		return (MS_EXIT_FAILURE);
	if (shell->input_str[0] == '\0')
		return (2);
	add_history(shell->input_str);
	shell->input_arr = ft_split(shell->input_str, ' ');
	// prt_input(shell->input_arr); /*To test what inputs are there*/
	return(MS_EXIT_SUCCESS);
}

int command_checker(t_minishell *shell, char *command)
{
	int i;

	i = 0;
	while (shell->std_commands[i])
	{
		if (ft_strncmp(shell->std_commands[i++], command, ft_strlen(command)) != 0)
			ft_printf("%s: command not found", command);
		return (MS_COMMAND_NOT_FOUND);
	}
	i = 0;
	while (shell->system_commands[i])
	{
		if (ft_strncmp(shell->system_commands[i++], command, ft_strlen(command)) == 0)
			return (SYSTEM_COMMAND);
	}
	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strncmp(shell->buildin_commands[i++], command, ft_strlen(command)) == 0)
			return (BUILDIN_COMMAND);
	}
	return (MS_EXIT_SUCCESS);
}
