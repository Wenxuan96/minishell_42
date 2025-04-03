/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:31:22 by wxi               #+#    #+#             */
/*   Updated: 2025/04/03 18:58:25 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_token(t_token **token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next_token;
		if (current->start)
			free(current->start);
		free (current);
		current = next;
	}
	*token_list = NULL;
}

void	ft_lstclear_env(t_environment **env_list)
{
	t_environment	*current;
	t_environment	*next;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		next = current->next_env_var;
		if (current->env_var)
			free(current->env_var);
		if (current->value)
			free(current->value);
		free (current);
		current = next;
	}
	*env_list = NULL;
}

void	ft_lstclear_redir(t_redirection **redir_list)
{
	t_redirection	*current;
	t_redirection	*next;

	if (!redir_list || !*redir_list)
		return ;
	current = *redir_list;
	while (current)
	{
		next = current->next_redir;
		if (current->file)
			free(current->file);
		free (current);
		current = next;
	}
	*redir_list = NULL;
}

void	ft_lstclear_process(t_process **process_list)
{
	t_process	*current;
	t_process	*next;
	int			i;

	i = 0;
	if (!process_list || !*process_list)
		return ;
	current = *process_list;
	while (current)
	{
		next = current->next_process;
		ft_lstclear_redir(&(current->redirections));
		while (current->command_arguments[i])
		{
			if (current->command_arguments[i])
				free(current->command_arguments[i]);
			i++;
		}
		free (current);
		current = next;
	}
	*process_list = NULL;
}
