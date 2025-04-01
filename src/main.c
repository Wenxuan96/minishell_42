/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/01 15:01:38 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd(t_environment **lst, t_environment *new)
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

t_environment	*ft_lstnew(void *content)
{
	t_environment	*new_node;

	new_node = malloc(sizeof(t_environment));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->index = -1;
	new_node->next = NULL;
	return (new_node);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int	i;
	t_environment	*env;
	char	**env_split;

	i = 0;
	char *env_var = envp[1];
	// printf("env var: %s\n", env_var);
	// printf("hello!\n");
	env = (t_environment)malloc(sizeof(t_environment));
	while (envp[i] != NULL)
	{
		env_split = ft_split(env[i], "=");
		env[i].env_var = env_split[0];
		env[i].value = env_split[1];
		i++;
	}
}
