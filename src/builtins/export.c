/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:36:59 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/04 14:30:06 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

char	**ft_split_env(char const *s, char c)
{
	int		i;
	char	**split;

	i = 0;
	if (!s || s[0] == c)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] != c)
		return (NULL);
	split = (char **)malloc((2 + 1) * sizeof(char *));
	split[0] = ft_substr(s, 0, i);
	split[1] = ft_strdup(s + i + 1);
	split[2] = NULL;
	return (split);
}

int	is_valid_quote(char *var)
{
	int	i;
	int	saw_equal;
	int	quote_count;

	i = 0;
	saw_equal = 0;
	quote_count = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '\"' || var[i] == '\'')
		{
			quote_count++;
			i++;
		}
		else if (var[i] == '=')
		{
			saw_equal = 1;
			i++;
		}
		if (quote_count != 2 || saw_equal == 1)
			return (0);
		else
			i++;
	}
	return (1);
}

char	*ft_trim_quotes(char *str)
{
	int		len;
	char	*trimmed_str;

	len = 0;
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"'
				&& str[len - 1] == '\"')))
		trimmed_str = ft_substr(str, 1, len - 2);
	else if (len >= 2 && (str[0] == '\'' || str[0] == '\"'))
		trimmed_str = ft_substr(str, 1, len - 1);
	else if (len >= 2 && (str[len - 1] == '\'' || str[len - 1] == '\"'))
		trimmed_str = ft_substr(str, 0, len - 2);
	else
		trimmed_str = ft_strdup(str);
	return (trimmed_str);
}

int	is_valid_env(char *var)
{
	int	i;

	i = 0;
	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
	while (var[i] != '\0')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_print2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int	export_builtin(t_process *process, t_minishell *shell)
{
	char			**split_vars;
	int				found;
	t_environment	*current;
	int				i;
	char			*temp;
	size_t			var_len;

	i = 1;
	var_len = 0;
	current = shell->env_list;
	if (process->command_arguments[1] == NULL)
	{
		prt_env_lst(shell->env_list);
		return (1);
	}
	while (process->command_arguments[i] != NULL)
	{
		split_vars = ft_split_env(process->command_arguments[i], '=');
		if (!split_vars || !split_vars[0])
		{
			display_shell_error(process, "export: not a valid identifier",
				EXEC_FAILURE);
			i++;
			continue ;
		}
		var_len = ft_strlen(split_vars[0]);
		if (split_vars[0][0] == '\'' || split_vars[0][0] == '\"'
			|| split_vars[0][var_len - 1] == '\'' || split_vars[0][var_len
			- 1] == '\"')
		{
			temp = split_vars[0];
			split_vars[0] = ft_trim_quotes(split_vars[0]);
			free(temp);
		}
		if (split_vars[1] && (split_vars[1][0] == '\''
				|| split_vars[1][0] == '\"'))
		{
			temp = split_vars[1];
			split_vars[1] = ft_trim_quotes(split_vars[1]);
			free(temp);
		}
		if (is_valid_env(split_vars[0]))
		{
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
					// break ;
				}
				current = current->next_env_var;
			}
			if (found == 0)
			{
				ft_var_lstadd_back(&shell->env_list,
					ft_new_var_lst(split_vars[0], split_vars[1]));
			}
		}
		else
			display_shell_error(process, "export: not a valid identifier",
				EXEC_FAILURE);
		free_2darray(split_vars);
		i++;
	}
	return (1);
}
