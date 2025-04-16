/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:00:12 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/16 10:45:40 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->system_commands = (const char *[]){"ls", "cat", "grep",
		"wc", "head", "tail", "chmod", "mv", "cp", "rm", "mkdir", "ps", "kill", NULL};
	shell->buildin_commands = (const char *[]){"cd", "echo", "exit",
		"pwd", "env", "unset", "alias", "export", "type", "set", "history", NULL};
	shell->std_commands = (const char *[]){"cd", "echo", "exit", "pwd",
		"env", "unset", "alias", "export", "type", "set", "history",
		"ls", "cat", "grep", "wc", "head", "tail", "chmod", "mv", "cp",
		"rm", "mkdir", "ps", "kill",NULL};
	shell->input_str = "\0";
	shell->input_arr = NULL;
	shell->token_list = NULL;
	shell->process_list = NULL;
	shell->num_processes = 0;
	shell->input_status = -1;
	shell->env_list = NULL;
	shell->pipes= NULL;	
}

// t_process	*new_process_lst(char **commands)
// {
// 	t_process	*new_process;
	
// 	new_process = malloc(sizeof(t_process));
// 	new_process->command_arguments = allocate_array(commands);
// 	new_process->redirections= NULL;
// 	new_process->input_fd = -1;
// 	new_process->is_pipeline = false;
// 	new_process->output_fd = -1;
// 	new_process->next_process= NULL;
// 	new_process->is_builtin = false;
// 	new_process->builtin = NULL;
// 	new_process->stopped = 0;
// 	new_process->completed = 0;
// }

t_token	*new_token_lst(char *token)
{
	t_token *new_token;
	
	(void)token;
	new_token = malloc(sizeof(t_token));
	new_token->in_quotes = false;
	new_token->is_dynamic = false;
	new_token->len = -1;
	new_token->type = INIT;
	new_token->start = NULL;
	new_token->next_token = NULL;
	return (new_token);
}