/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var_epansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:43:09 by wxi               #+#    #+#             */
/*   Updated: 2025/06/22 19:23:19 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_val(int *n, char **a, char **b, char **c)
{
	*n = 0;
	*a = NULL;
	*b = NULL;
	*c = NULL;
}

void	free_var(char *before, char *after, char *tmp, char *result)
{
	free(before);
	free(after);
	free(tmp);
	free(result);
}

bool	find_dollar(char *token_val)
{
	bool		dollar_found;
	size_t		i;

	i = 0;
	dollar_found = false;
	while (i < ft_strlen(token_val))
	{
		if (token_val[i++] == '$')
			dollar_found = true;
	}
	return(dollar_found);
}

char	*ft_getenv(char *var_name, t_minishell *shell)
{
	t_environment	*current;

	current = shell->env_list;
	while(current != NULL)
	{
		if (ft_strcmp(current->env_var, var_name) == 0)
			return	(ft_strdup(current->value));
		current = current->next_env_var;
	}
	return (NULL);
}