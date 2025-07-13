/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:31:22 by wxi               #+#    #+#             */
/*   Updated: 2025/07/13 09:49:22 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
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
		free(current);
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
		free(current);
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
		free(current);
		current = next;
	}
	*redir_list = NULL;
}

void	ft_lstclear_process(t_process **process_list)
{
	t_process	*current;
	t_process	*next;
	int			i;

	if (!process_list || !*process_list)
		return ;
	current = *process_list;
	while (current)
	{
		next = current->next_process;
		ft_lstclear_redir(&current->redirections);
		if (current->command_arguments)
		{
			i = 0;
			while (current->command_arguments[i])
				free(current->command_arguments[i++]);
			free(current->command_arguments);
		}
		if (current->is_builtin && current->builtin)
			free(current->builtin);
		free(current);
		current = next;
	}
	*process_list = NULL;
}

void	ft_exit(t_minishell *shell, char *error_msg)
{
	if (error_msg)
		ft_printf("%s\n", error_msg);
	else if (!shell && !error_msg)
		exit(EXEC_SUCCESS);
	if (shell)
	{
		ft_lstclear_token(&shell->token_list);
		ft_lstclear_env(&shell->env_list);
		ft_lstclear_process(&shell->process_list);
		if (shell->input_str)
			free(shell->input_str);
		if (shell->pipes)
		{
			free_pipes(shell);
			shell->pipes = NULL;
		}
		shell = NULL;
	}
	exit(EXEC_SUCCESS);
}
