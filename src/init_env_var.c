/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:20:32 by tanja             #+#    #+#             */
/*   Updated: 2025/04/08 15:51:24 by wxi              ###   ########.fr       */
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

//This test function prints all env_var
void	prt_env_lst(t_environment **env_list)
{
	t_environment	**current;

	current = env_list;
	while ((*current) != NULL)
	{
		printf("var : %s\n", (*current)->env_var);
		printf("val : %s\n", (*current)->value);
		current = &(*current)->next_env_var;
	}
	printf("end of env list\n");
}

//This function creates a linked list of available environment variables
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
		ft_var_lstadd_back(env_list, new_env);
	}
	prt_env_lst(env_list);
    return (1);
}

// int	create_env_lst(char **envp, t_environment **env_list)
// {
// 	t_environment	*new_env_node;
// 	char	**env_split;
// 	int	i;

// 	i = 0;
// 	*env_list = NULL;
// 	while (envp[i] != NULL)
// 	{
// 		env_split = ft_split(envp[i], '=');
// 		if (!env_split)
// 			return (0);
// 		new_env_node = ft_new_var_lst(env_split[0], env_split[1]);
// 		ft_var_lstadd_back(env_list, new_env_node);
// 		i++;
// 	}
// 	while (env_list)
// 	{
// 		printf("var : %s\n", (*env_list)->env_var);
// 		printf("val : %s\n", (*env_list)->value);
// 		env_list = &(*env_list)->next_env_var;
// 	}
//     return (1);
// }
