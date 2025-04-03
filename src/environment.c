/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:20:32 by tanja             #+#    #+#             */
/*   Updated: 2025/04/03 15:33:50 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   create_env_lst(char **envp, t_environment **env_list)
{
	t_environment	*new_env_node;
	char	**env_split;
	int	i;

	i = 0;
	*env_list = NULL;
	while (envp[i] != NULL)
	{
		env_split = ft_split(envp[i], '=');
		if (!env_split)
			return (0);
		new_env_node = ft_new_var_lst(env_split[0], env_split[1]);
		ft_var_lstadd_back(env_list, new_env_node);
		i++;
	}
	while (env_list)
	{
		printf("var : %s\n", (*env_list)->env_var);
		printf("val : %s\n", (*env_list)->value);
		env_list = &(*env_list)->next_env_var;
	}
    return (1);
}
