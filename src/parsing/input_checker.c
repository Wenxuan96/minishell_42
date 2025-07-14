/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:52 by wxi               #+#    #+#             */
/*   Updated: 2025/07/14 17:18:56 by tignatov         ###   ########.fr       */
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

static int	wit_space_str(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->input_str[i])
	{
		if (shell->input_str[i] != ' ' && shell->input_str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	skip_white_space(t_minishell *shell)
{
	int		start;
	int		end;
	char	*tmp;

	start = 0;
	while (shell->input_str[start] == ' ' || shell->input_str[start] == '\t')
		start++;
	end = ft_strlen(shell->input_str) - 1;
	while (end >= start && (shell->input_str[end] == ' '
			|| shell->input_str[end] == '\t'))
		end--;
	tmp = ft_substr(shell->input_str, start, end - start + 1);
	if (!tmp)
		return (EXEC_FAILURE);
	free(shell->input_str);
	shell->input_str = tmp;
	return (EXEC_SUCCESS);
}

static int	special_chr_ctrl(t_minishell *shell)
{
	if (skip_white_space(shell) == EXEC_FAILURE)
	{
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
		return (EXEC_FAILURE);
	}
	return (EXEC_SUCCESS);
}

int	read_input(int argc, t_minishell *shell)
{
	int	init;
	int	error;

	error = EXEC_SUCCESS;
	init = 0;
	if (init == 0 && argc != 1)
		ft_exit(NULL, "Expecting <./minishell> to start the program.");
	else
		init = 1;
	shell->input_str = readline("minishell$ ");
	if (!shell->input_str)
		ft_exit(shell, "exit");
	else if (shell->input_str[0] == '\0' || wit_space_str(shell) == 1)
		return (EX_BADUSAGE);
	else if (ft_strcmp(shell->input_str, "\'\'") == 0
		|| ft_strcmp(shell->input_str, "\"\"") == 0)
		return (CMD_NOTFOUND);
	error = special_chr_ctrl(shell);
	add_history(shell->input_str);
	if (tokenize_input(shell) != EXEC_SUCCESS
		|| init_processlst(shell) != EXEC_SUCCESS)
		error = EXEC_FAILURE;
	free_tokenlst(shell);
	free(shell->input_str);
	return (error);
}
