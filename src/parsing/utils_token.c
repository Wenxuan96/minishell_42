/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:33 by wxi               #+#    #+#             */
/*   Updated: 2025/04/28 16:47:10 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tokenlst(t_minishell *shell)
{
	t_token	*current;

	if (!shell->token_list)
		return ;
	while (shell->token_list)
	{
		current = shell->token_list->next_token;
		free(shell->token_list->token_val);
		free(shell->token_list);
		shell->token_list = current;
	}
	shell->token_list = NULL;
}

void	ms_token_add_back(t_token **token_lst, t_token *new_token)
{
	t_token *current;

	if (new_token == NULL)
		return ;
	if (*token_lst == NULL)
	{
		*token_lst = new_token;
		return ;
	}
	current = *token_lst;
	while (current->next_token != NULL)
		current = current->next_token;
	current->next_token = new_token;
}

int redir_checker(char *command)
{
	if (ft_strncmp(">>", command, 2) == 0 && command[2] == '\0')
		return (OUTPUT_APPEND);
	else if (ft_strncmp(">", command, 1) == 0 && command[1] == '\0')
		return (OUTPUT);
	else if (ft_strncmp("<<", command, 2) == 0 && command[2] == '\0')
		return (HEREDOC);
	else if (ft_strncmp("<", command, 1) == 0 && command[1] == '\0')
		return (INPUT);
	return (CMD_NOTFOUND);
}

int token_checker(char *command)
{
	if ((ft_strlen(command) == 1 && command[0] == '|'))
	{
		ft_printf("it is pipeline.\n");
		return(PIPELINE);
	}
	if (redir_checker(command) != CMD_NOTFOUND)
		return (REDIRECTION);
	return (WORD);
}
