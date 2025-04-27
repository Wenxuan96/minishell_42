/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:20:32 by tanja             #+#    #+#             */
/*   Updated: 2025/04/24 16:22:33 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_var_lstadd_back(t_environment **lst, t_environment *new)
{
	t_environment	*current;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next_env_var != NULL)
		current = current->next_env_var;
	current->next_env_var = new;
}

t_environment	*ft_new_var_lst(char *variable, char *value)
{
	t_environment	*new_node;

	new_node = malloc(sizeof(t_environment));
	if (!new_node)
		return (NULL);
	new_node->env_var = variable;
	new_node->value = value;
	new_node->next_env_var = NULL;
	return (new_node);
}

int	create_env_lst(t_environment **env_list, char **envp)
{
	t_environment	*new_env;
	char			**env_split;
	int				i;

	i = 0;
	*env_list = NULL;
	while (envp[i] != NULL)
	{
		env_split = ft_split(envp[i++], '=');
		if (!env_split)
			return (0);
		new_env = ft_new_var_lst(env_split[0], env_split[1]);
		if (!new_env)
			return(ft_lstclear_env(env_list), 0);
		ft_var_lstadd_back(env_list, new_env);
	}
	// prt_env_lst(env_list);
    return (1);
}

void	ft_lstclear_envvars(t_environment *envvar_list)
{
	t_environment	*temp;
	
	while (envvar_list != NULL)
	{
		temp = envvar_list->next_env_var;
		free(envvar_list->env_var);
		free(envvar_list->value);
		free(envvar_list);
		envvar_list = temp;
	}
}

void	ft_lstclear_process_envvars(t_process **process)
{
	t_process	*current;
	
	current = *process;
	while (current != NULL)
	{
		ft_lstclear_envvars(current->env_vars);
		current->env_vars = NULL;
		current = current->next_process;
	}
}
