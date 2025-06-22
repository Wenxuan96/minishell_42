/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:28:10 by wxi               #+#    #+#             */
/*   Updated: 2025/06/22 17:52:51 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*expand_token(t_token *token, t_minishell *shell)
{
	int		i;
	int		var_start;
	char	*before;
	char	*after;
	char	*new_result;
	int		var_len;
	char	*tmp;
	char	*var_name;
	char	*var_val;
	char	*result;

	i = 0;
	init_val(&var_start, &before, &after, &new_result);
	init_val(&var_len, &tmp, &var_name, &var_val);
	result = ft_strdup(token->token_val);
	if (!result)
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
	while (result[i])
	{
		if (result[i] == '$')
		{
			var_start = i;
			i++;
			if (result[i] == '$')
			{
				var_val = ft_itoa(getpid());
				i++; // consume both $$
			}
			else if (result[i] == '?')
			{
				var_val = ft_itoa(g_exit_status);
				i++; // consume $?
			}
			else if (result[i] == '\0')
				var_val = ft_strdup("$");
			else
			{
				while (ft_isalnum(result[i + var_len]) || result[i + var_len] == '_')
					var_len++;
				var_name = ft_substr(result, i, var_len);
				if (!var_name)
					display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
				var_val = ft_getenv(var_name, shell);
				free(var_name);
				if (!var_val)
					var_val = ft_strdup("");
				i += var_len;
			}
			before = ft_substr(result, 0, var_start);
			after = ft_strdup(result + i);
			tmp = ft_strjoin(before, var_val);
			new_result = ft_strjoin(tmp, after);
			free(before);
			free(after);
			free(tmp);
			free(result);
			result = new_result;
			i = var_start + ft_strlen(var_val); // Move i past the inserted value
			if (var_val)
				free(var_val);
		}
		else
			i++;
	}
	return (result);
}

char	*def_expansion(t_token *token, t_minishell *shell)
{
	char	*commands;
	int		i;

	commands = ft_strdup(token->token_val);
	i = 0;
	if (find_dollar(token->token_val) == true && 
			(token->in_quotes == false || token->double_quoted == true))
	{
		while (token->token_val[i])
		{
			if (token->token_val[i] == '$')
			{
				i++;
				if (ft_strchr(" \\|<>", token->token_val[i]) != NULL)
					return (commands);
			}
			i++;
		}
		free (commands);
		commands = expand_token(token, shell);
	}
	return (commands);
}
