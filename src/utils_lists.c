/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:03:57 by tanja             #+#    #+#             */
/*   Updated: 2025/04/03 17:31:07 by wxi              ###   ########.fr       */
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
