/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prcs_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:21 by wxi               #+#    #+#             */
/*   Updated: 2025/06/06 17:37:49 by wxi              ###   ########.fr       */
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

int	count_commands(t_token	**token)
{
	int		i;
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
	return (i);
}

char	*get_file(t_token *token)
{
	char	*redir_file;

	redir_file = NULL;
	if (token->next_token->type == WORD)
		redir_file = token->next_token->token_val;
	return (redir_file);
}

void	prt_cmds(t_process *process_lst)
{
	t_process	*current;
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

void	print_process(t_minishell *shell)
{
	t_process		*current;
	t_redirection	*curr_redir;

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