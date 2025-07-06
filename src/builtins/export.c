/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:36:59 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/06 17:30:02 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	process_quotes(char **split_vars)
{
	char	*temp;
	size_t	var_len;

	var_len = ft_strlen(split_vars[0]);
	if (var_len > 0 && (split_vars[0][0] == '\'' || split_vars[0][0] == '\"'
			|| split_vars[0][var_len - 1] == '\'' || split_vars[0][var_len
			- 1] == '\"'))
	{
		temp = split_vars[0];
		split_vars[0] = ft_trim_quotes(split_vars[0]);
		free(temp);
	}
	if (split_vars[1] && (split_vars[1][0] == '\'' || split_vars[1][0] == '\"'))
	{
		temp = split_vars[1];
		split_vars[1] = ft_trim_quotes(split_vars[1]);
		free(temp);
	}
}

void	add_var_tolist(t_minishell *shell, char **split_vars)
{
	t_environment	*current;
	int				found;

	found = 0;
	current = shell->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_var, split_vars[0]) == 0)
		{
			free(current->value);
			if (split_vars[1] != NULL)
				current->value = ft_strdup(split_vars[1]);
			else
				current->value = NULL;
			found = 1;
			break ;
		}
		current = current->next_env_var;
	}
	if (found == 0)
	{
		ft_var_lstadd_back(&shell->env_list, ft_new_var_lst(split_vars[0],
				split_vars[1]));
	}
}

void	process_one_var(t_process *process, t_minishell *shell, int *i)
{
	char	**split_vars;

	split_vars = ft_split_env(process->command_arguments[*i], '=');
	if (!split_vars || !split_vars[0])
	{
		display_shell_error(process, "export: not a valid identifier",
			EXEC_FAILURE);
		(*i)++;
		return ;
	}
	process_quotes(split_vars);
	if (is_valid_env(split_vars[0]))
		add_var_tolist(shell, split_vars);
	else
		display_shell_error(process, "export: not a valid identifier",
			EXEC_FAILURE);
	free_2darray(split_vars);
	(*i)++;
}

int	export_builtin(t_process *process, t_minishell *shell)
{
	int	i;

	i = 1;
	if (process->command_arguments[1] == NULL)
		return (prt_env_lst(shell->env_list), 1);
	while (process->command_arguments[i] != NULL)
		process_one_var(process, shell, &i);
	return (1);
}
