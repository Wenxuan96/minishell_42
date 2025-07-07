/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_get_env_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:13:36 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 12:47:21 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_vars(t_environment *var_list)
{
	int	num_vars;

	num_vars = 0;
	while (var_list != NULL)
	{
		if (var_list->value != NULL)
			num_vars++;
		var_list = var_list->next_env_var;
	}
	return (num_vars);
}

char	**env_convert_to_arr(t_environment *var_list, char **envvars)
{
	int	i;
	int	total_len;

	i = 0;
	total_len = 0;
	while (var_list != NULL)
	{
		if (var_list->value != NULL)
		{
			total_len = ft_strlen(var_list->env_var)
				+ ft_strlen(var_list->value) + 2;
			envvars[i] = (char *)malloc(total_len * sizeof(char));
			if (!envvars[i])
				return (free_2darray(envvars), NULL);
			ft_strlcpy(envvars[i], var_list->env_var, total_len);
			ft_strlcat(envvars[i], "=", total_len);
			ft_strlcat(envvars[i], var_list->value, total_len);
			i++;
		}
		var_list = var_list->next_env_var;
	}
	envvars[i] = NULL;
	return (envvars);
}

char	**execve_get_envvars(t_minishell *shell)
{
	char	**envvars;
	int		num_vars;

	num_vars = count_vars(shell->env_list);
	envvars = (char **)malloc((num_vars + 1) * sizeof(char *));
	if (!envvars)
		return (NULL);
	return (env_convert_to_arr(shell->env_list, envvars));
}
