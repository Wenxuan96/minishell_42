/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_process__2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:36:07 by wxi               #+#    #+#             */
/*   Updated: 2025/05/12 13:01:39 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	count_pipes(t_minishell *shell)
{
	int		i;
	t_token	*current;
	
	i = 1;
	current = shell->token_list;
	while (current)
	{
		if ((ft_strcmp(current->token_val, "|") == 0)
			&& (ft_strlen(current->token_val) == 1) && 
			current->type == PIPELINE)
			i++;	
		current = current->next_token;
	}
	return (i);
}

char	**get_commands(t_token	**token)
{
	int		i;
	char	**commands;
	t_token	*current;
	
	i = 0;
	if ((*token)->type == PIPELINE && (*token)->next_token != NULL)
		*token = (*token)->next_token;
	current = *token;
	while (current && current->type != PIPELINE)
	{
		if (current->type == REDIRECTION)
		{
			current = current->next_token;
			if (current)
				current = current->next_token;
		}
		else
		{
			i++;
			current = current->next_token;
		}
	}
	commands = (char **)malloc((i + 1) * sizeof(char *));
	if (!commands)
		return (display_shell_error("memory allocation failed", EXEC_FAILURE), NULL);
	i = 0;
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
			commands[i] = strdup((*token)->token_val);
			if (!commands[i])
			{
				free_2darray(commands);
                display_shell_error("memory allocation failed", EXEC_FAILURE);
                return (NULL);
			}
			(*token) = (*token)->next_token;
			i++;
		}
	}
	commands[i] = NULL;
	return (commands);
}

void prt_cmds(t_process *process_lst)
{
	t_process *current;
	int			i;
	
	i = 0;
	current = process_lst;
	while(current)
	{
		ft_printf("process commands are: ");
		while (current->command_arguments[i])
			ft_printf("[%s] ", current->command_arguments[i++]);
		current = current->next_process;
		i = 0;
	}	
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
char	*get_file(t_token *token)
{
	char	*redir_file;

	redir_file = NULL;
	if (token->next_token->type == WORD)
		redir_file = token->next_token->token_val;
	return (redir_file);
}

int	parse_redirection(t_minishell *shell)
{
	t_process *current_process;
	t_token		*current_token;
	t_redir_type type;
	char 		*file;

	current_process = shell->process_list;
	current_token = shell->token_list;
	file = NULL;
	if (current_token->type == PIPELINE && current_token->next_token != NULL)
		current_token = current_token->next_token;
	while (current_process != NULL)
	{
		while (current_token != NULL)
		{
			if (current_token->type == PIPELINE)
			{
				current_token = current_token->next_token;
				break ;
			}
			if (current_token->type == REDIRECTION)
			{
				type = get_redir_type(current_token);
				file = ft_strdup(get_file(current_token));
				if (!current_process->redirections)
					current_process->redirections = new_redir_lst(type, file);
				else
					redir_lst_add_back(new_redir_lst(type, file), &current_process->redirections);
				current_token = current_token->next_token;
				if (current_token->next_token)
					current_token = current_token->next_token;
				}
			else
				current_token = current_token->next_token;
		}
		// if (current_process->redirections)
		// {
		// 	printf("redirection type: %u\n", current_process->redirections->type);
		// 	printf("redirection file: %s\n", current_process->redirections->file);
		// }
		current_process = current_process->next_process;
	}
	return (1);
}

void	print_process(t_minishell *shell)
{
	t_process   *current;
	t_redirection *curr_redir;

    current = shell->process_list;
	printf("num_proc: %i\n", shell->num_processes);
    while (current != NULL)
	{
		curr_redir = current->redirections;
		printf("command :%s, %s\n", current->command_arguments[0], current->command_arguments[1]);
		if (curr_redir)
		{
			while (curr_redir)
			{
				printf("redirection type: %u\n", curr_redir->type);
				printf("redirection file: %s\n", curr_redir->file);
				curr_redir = curr_redir->next_redir;
			}
		}
		if (current->is_builtin == 1)
			printf("type: %u\n", current->builtin->type);
		current = current->next_process;
	}
}

int init_processlst(t_minishell *shell)
{
	char		**arr_commands;
	// t_process	*process_lst;
	t_token		*current;
	int			i;

	i = 0;
	current = shell->token_list;
	shell->num_processes = count_pipes(shell);
	// printf("num proc: %i\n", shell->num_processes);
	while (i < shell->num_processes)
	{
		arr_commands = get_commands(&current);
		if (!arr_commands)
            return (0);
		if (!shell->process_list)
			shell->process_list = new_process_lst(shell, arr_commands);
		else
			process_lst_add_back(new_process_lst(shell, arr_commands), &shell->process_list);
		free_2darray(arr_commands);
		i++;
	}
	// free_2darray(arr_commands);
	parse_redirection(shell);
	parse_builtin(shell);
	// print_process(shell);
	// prt_cmds(shell->process_list);
	return (1);
}
