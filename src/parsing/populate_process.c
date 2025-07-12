/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:36:07 by wxi               #+#    #+#             */
/*   Updated: 2025/07/12 12:17:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	**malloc_mem(t_token **token, int *i)
{
	char	**commands;

	*i = 0;
	commands = (char **)malloc((count_commands(token) + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	return (commands);
}

char	**get_commands(t_token	**token, t_minishell *shell)
{
	int		i;
	char	**commands;

	commands = malloc_mem(token, &i);
	if (!commands)
		return (NULL);
	while ((*token) && (*token)->type != PIPELINE)
	{
		if ((*token)->type == REDIRECTION)
			expand_n_skip(token, shell);
		else
		{
			commands[i] = def_expansion(*token, shell);
			if (!commands[i])
				return (free_2darray(commands), NULL);
			(*token) = (*token)->next_token;
			i++;
		}
	}
	commands[i] = NULL;
	return (commands);
}

int	parse_redirection(t_minishell *shell)
{
	t_process		*current_process;
	t_token			*current_token;
	t_redir_type	type;
	char			*file;

	current_process = shell->process_list;
	current_token = shell->token_list;
	file = NULL;
	type = -1;
	if (current_token->type == PIPELINE && current_token->next_token != NULL)
		current_token = current_token->next_token;
	while (current_process != NULL)
	{
		if (!find_n_def_redir(type, file, current_process, &current_token))
			return (0);
		current_process = current_process->next_process;
	}
	return (1);
}

void	add_process(char **arr_commands, t_minishell *shell)
{
	t_process	*new_process;

	if (!arr_commands)
		exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
	new_process = new_process_lst(shell, arr_commands);
	if (!new_process)
		exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
	if (!shell->process_list)
		shell->process_list = new_process;
	else
		process_lst_add_back(new_process, &shell->process_list);
}

int	init_processlst(t_minishell *shell)
{
	char		**arr_commands;
	t_token		*current;
	int			i;

	i = 0;
	current = shell->token_list;
	shell->num_processes = count_pipes(shell);
	while (i < shell->num_processes)
	{
		arr_commands = get_commands(&current, shell);
		add_process(arr_commands, shell);
		free_2darray(arr_commands);
		i++;
	}
	if (!parse_redirection(shell))
		exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
	parse_builtin(shell);
	return (EXEC_SUCCESS);
}
