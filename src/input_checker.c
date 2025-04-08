/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/04/08 18:29:42 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Step 1: read from stdinput and save the input
Signal is needed to continue reading user input
if signal is received, read and malloc stdin
*/

int archive_input(char	*input_str, t_minishell *shell)
{
	static int		i = 0;
	static int		j = 0;
	char			**new_archive;

	while (shell->input_archive && shell->input_archive[i])
		i++;
	new_archive = malloc(sizeof(char *) * (i + 1 + 1));
	if (!new_archive)
		return (MS_EXIT_FAILURE);
	while (j < i)
	{
		new_archive[j] = shell->input_archive[j];
		j++;
	}
	new_archive[i] = ft_strdup(input_str);
	if (!new_archive[i])
	{
		free (new_archive);
		return (MS_EXIT_FAILURE);
	}
	new_archive[i + 1] = NULL;
	free(shell->input_archive);
	shell->input_archive = new_archive;
	return (MS_EXIT_SUCCESS);
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
	if (!shell->input_str) /*When ctrl+D is pressed, break the loop, clean memory and exit */
		return (0);
	if (shell->input_str[0] == '\0')
		return (2);
	if (archive_input(shell->input_str, shell) == MS_EXIT_FAILURE)
		ft_exit(shell, "Malloc failure.");
	
	return(1);
}