/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:00:12 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/14 12:56:46 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->system_commands = (const char *[]){"cd", "echo", "exit",
		"pwd", "env", "setenv", "unsetenv", "export", "ls", NULL};
	shell->input_str = "\0";
	shell->input_arr = NULL;
	shell->token_list = NULL;
	shell->process_list = NULL;
	shell->num_processes = 0;
	shell->input_status = -1;
	shell->env_list = NULL;
	shell->pipes= NULL;	
}

t_process	*new_process_lst(char **commands)
{
	t_process	*new_process;
	
	new_process = malloc(sizeof(t_process));
	new_process->command_arguments = allocate_array(commands);
	new_process->redirections= NULL;
	new_process->input_fd = -1;
	new_process->is_pipeline = -1;
	new_process->output_fd = -1;
	new_process->next_process= NULL;
	new_process->is_builtin = 0;
	new_process->builtin = NULL;
	new_process->stopped = 0;
	new_process->completed = 0;
	return (new_process);
}
