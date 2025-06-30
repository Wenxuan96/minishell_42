/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/06/30 20:21:16 by wxi              ###   ########.fr       */
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
		ft_printf(" [%s: %d]", current->token_val, current->type);
		current = current->next_token;
	}
	ft_printf(".\n");
}

// static void	free_shell(t_minishell *shell)
// {
// 	free(shell->input_str);
// 	free(shell->token_list);
// 	free(shell);
// 	shell = NULL;
// 	exit(g_exit_status);
// }

static int wit_space_str(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->input_str[i])
	{
		if (shell->input_str[i] != ' ' && shell->input_str[i] != '\t')
			return (0);
		i++;
	}
	return(1);
}

int	read_input(int argc, t_minishell *shell)
{
	int	init;

	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str)
		ft_exit(shell, "exit");
	if (shell->input_str[0] == '\0' || wit_space_str(shell) == 1)
		return (2);
	if (ft_strcmp(shell->input_str, "\'\'") == 0 ||
		ft_strcmp(shell->input_str, "\"\"") == 0)
		return (CMD_NOTFOUND);
	add_history(shell->input_str);
	if (tokenize_input(shell) != EXEC_SUCCESS)
		return (EXEC_FAILURE);
	// prt_tokenlst(shell);
	if (init_processlst(shell) != EXEC_SUCCESS)
		return (EXEC_FAILURE);
	free_tokenlst(shell);
	free(shell->input_str);
	return(EXEC_SUCCESS);
}
