/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:36:07 by wxi               #+#    #+#             */
/*   Updated: 2025/06/11 17:43:50 by wxi              ###   ########.fr       */
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
	return(commands);
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
		{
			(*token) = (*token)->next_token;
			if (*token != NULL)
				(*token) = (*token)->next_token;
		}
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

t_redir_type	get_redir_type(t_token *token)
{
	t_redir_type	type;

	type = NONE;
	if (ft_strcmp(token->token_val, ">") == 0 && token->token_val[1] == '\0')
		type = OUTPUT;
	else if (ft_strcmp(token->token_val, "<") == 0 && token->token_val[1] == '\0')
		type = INPUT;
	else if (ft_strcmp(token->token_val, ">>") == 0 && token->token_val[2] == '\0')
		type = OUTPUT_APPEND;
	else if (ft_strcmp(token->token_val, "<<") == 0 && token->token_val[2] == '\0')
		type = HEREDOC;
	return (type);
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
	if (current_token->type == PIPELINE && current_token->next_token != NULL)
		current_token = current_token->next_token;
	while (current_process != NULL)
	{
		while (current_token != NULL)
		{
			if (current_token->type == REDIRECTION)
			{
				type = get_redir_type(current_token);
				file = ft_strdup(get_file(current_token));
				if (!file)
					return (0);
				if (!current_process->redirections)
				{
					current_process->redirections = new_redir_lst(type, file);
					if (!current_process->redirections)
						return (0);
				}
				else
					redir_lst_add_back(new_redir_lst(type, file), &current_process->redirections);
				current_token = current_token->next_token;
				if (current_token->next_token)
					current_token = current_token->next_token;
				}
			else
				current_token = current_token->next_token;
		}
		current_process = current_process->next_process;
	}
	return (1);
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
		if (!arr_commands)
			exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
		if (!shell->process_list)
		{
			shell->process_list = new_process_lst(shell, arr_commands);
			if (!shell->process_list)
				exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
		}
		else
			process_lst_add_back(new_process_lst(shell, arr_commands), &shell->process_list);
		free_2darray(arr_commands);
		i++;
	}
	if (!parse_redirection(shell))
		exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
	parse_builtin(shell);
	return (EXEC_SUCCESS);
}
