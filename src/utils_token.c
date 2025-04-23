/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:33 by wxi               #+#    #+#             */
/*   Updated: 2025/04/22 12:39:02 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prt_tokenlst(t_minishell *shell)
{
	t_token *current;

	current = shell->token_list;
	if (!current)
		return ;
	ft_printf("current tokens are:");
	while (current != NULL)
	{
		ft_printf(" [%s]", current->token_val);
		current = current->next_token;
	}
	ft_printf(".\n");
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
	return (MS_TARGET_NOT_FOUND);
}

int token_checker(char *command)
{
	if (ft_strlen(command) == 1 && command[0] == '|')
		return(PIPELINE);
	if (redir_checker(command) != MS_TARGET_NOT_FOUND)
		return (REDIRECTION);
	return (WORD);
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

// for normal tokens
void	def_token(t_minishell *shell, int t_len, int t_start)
{
	t_token	*new_token;
	char *sub;

	sub = ft_substr(shell->input_str, t_start, t_len);
	if (!sub || sub[0] == '\0') // <- 🔥 important check
	{
		free(sub);
		return ;
	}
	new_token = new_token_lst(sub);
	new_token->in_quotes = false; //write check quote()
	new_token->len = t_len;
	new_token->start = t_start;
	new_token->type = token_checker(new_token->token_val);
	new_token->next_token = NULL;
	ms_token_add_back(&shell->token_list, new_token);
}

void	def_special_token(t_minishell *shell, int *i)
{
	while (shell->input_str[*i] == ' ' || shell->input_str[*i] == '\t')
		(*i)++;
	if (ft_strncmp(shell->input_str + *i, "||", 2) == 0
		|| ft_strncmp(shell->input_str + *i, "&&", 2) == 0
		|| ft_strncmp(shell->input_str + *i, "<<", 2) == 0
		|| ft_strncmp(shell->input_str + *i, ">>", 2) == 0)
	{
		def_token(shell, 2, *i);
		(*i) += 2;
	}
	else if (ft_strchr("|&<>", shell->input_str[*i]) != NULL)
	{
		def_token(shell, 1, *i);
		(*i)++;
	}
}

