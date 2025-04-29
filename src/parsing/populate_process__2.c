/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_process__2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:36:07 by wxi               #+#    #+#             */
/*   Updated: 2025/04/29 09:47:47 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_commands(t_token	**current)
{
	int		i;
	char	**commands;
	t_token	*process_current;
	
	i = 0;
	if ((*current)->type == PIPELINE && (*current)->next_token != NULL)
		*current = (*current)->next_token;
	process_current = *current;
	while (process_current && process_current->type != PIPELINE)
	{
		i++;
		process_current = process_current->next_token;
	}
	commands = (char **)malloc((i + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	i = 0;
	while ((*current) && (*current)->type != PIPELINE)
	{
		commands[i] = strdup((*current)->token_val);
		(*current) = (*current)->next_token;
		i++;
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

// int create_pipes(t_minishell *shell)
// {
// 	t_process   *process_lst;
// 	t_process   *current;
// 	// char *p1_cmd[] = {"ls", NULL};
// 	// char *p2_cmd[] = {"grep", "test", NULL};
// 	// char *p3_cmd[] = {"wc", "-l", NULL};

// 	char *p1_cmd[] = {"echo", "hello", NULL};
// 	char *p2_cmd[] = {"cat", NULL};
// 	char *p3_cmd[] = {"wc", "-c", NULL};

// 	process_lst = NULL;
// 	process_lst_add_back(new_process_lst(shell, p1_cmd), &process_lst);
// 	process_lst_add_back(new_process_lst(shell, p2_cmd), &process_lst);
// 	process_lst_add_back(new_process_lst(shell, p3_cmd), &process_lst);
// 	shell->process_list = process_lst;
// 	current = process_lst;
// 	while (current != NULL)
// 	{
// 		// printf("%s\n", current->command_arguments[0]);
// 		current = current->next_process;
// 		shell->num_processes++;
// 	}
// 	current = process_lst;
// 	if (shell->num_processes > 1)
// 	{
// 		while (current != NULL)
// 		{
// 			current->is_pipeline = 1;
// 			current = current->next_process;
// 		}
// 	}
// 	shell->pipes = allocate_pipes(shell->num_processes - 1);
// 	return (1);
// }

int init_processlst(t_minishell *shell)
{
	char		**arr_commands;
	// t_process	*process_lst;
	t_token		*current;
	int			i;

	i = 0;
	current = shell->token_list;
	// process_lst = NULL;
	shell->num_processes = count_pipes(shell);
	while (i < shell->num_processes)
	{
		arr_commands = get_commands(&current);
		if (!arr_commands)
            return (0);
		if (!shell->process_list)
		shell->process_list = new_process_lst(shell, arr_commands);
		else
			process_lst_add_back(new_process_lst(shell, arr_commands), &shell->process_list);
		i++;
	}
	prt_cmds(shell->process_list);
	return (1);
}
