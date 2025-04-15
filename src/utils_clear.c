/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:31:22 by wxi               #+#    #+#             */
/*   Updated: 2025/04/15 15:23:50 by wxi              ###   ########.fr       */
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
		if (current->start && current->is_dynamic)
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
		if (current->file && current->is_dynamic)
			free(current->file);
		free (current);
		current = next;
	}
	*redir_list = NULL;
}

void	ft_lstclear_process(t_process **process_list) //   + clean env_vars
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
		ft_lstclear_redir(&(current->redirections));
		ft_lstclear_process_envvars(&current);
		if (current->command_arguments)
		{
			i = 0;
			while (current->command_arguments[i])
				free (current->command_arguments[i++]);
			free (current->command_arguments);
		}
		free (current);
		current = next;
	}
	*process_list = NULL;
}

void	ft_exit(t_minishell *shell, char *error_msg)
{
	int	i;

	i = 0;
	if (shell->input_status == MS_EXIT_FAILURE && error_msg)
		ft_printf("%s\n", error_msg);
	else if (error_msg)
		ft_printf("Error: %s.\n", error_msg);
	else if (!shell && !error_msg)
		exit(MS_EXIT_SUCCESS);
	else
	{
		ft_lstclear_token(&shell->token_list);
		ft_lstclear_env(&shell->env_list);
		ft_lstclear_process(&shell->process_list);
		if (shell->input_str)
			free (shell->input_str);
		if (shell->pipes)
			free_pipes(shell);
		shell = NULL;
	}
	exit(MS_EXIT_SUCCESS);
}
