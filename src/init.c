/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:00:12 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/09 13:33:16 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell)
{
	static const char *const	system_commands[] = {"ls", "cat", "grep", "wc",
		"head", "tail", "chmod", "mv", "cp", "rm", "mkdir", "ps", "kill",
		"./minishell", NULL};
	static const char *const	buildin_commands[] = {"cd", "echo", "exit",
		"pwd", "env", "unset", "alias", "export", "type", "set", "history",
		NULL};

	shell->system_commands = (const char **)system_commands;
	shell->buildin_commands = (const char **)buildin_commands;
	shell->input_str = NULL;
	shell->token_list = NULL;
	shell->process_list = NULL;
	shell->num_processes = 0;
	shell->input_status = -1;
	shell->env_list = NULL;
	shell->pipes = NULL;
	shell->exit_status = 0;
	shell->heredoc_inquote = false;
}

t_token	*new_token_lst(char *token)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token_val = ft_strdup(token);
	new_token->double_quoted = false;
	new_token->in_quotes = false;
	if (!new_token->token_val)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next_token = NULL;
	return (new_token);
}
