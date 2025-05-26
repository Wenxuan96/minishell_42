/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:28:10 by wxi               #+#    #+#             */
/*   Updated: 2025/05/26 12:12:26 by wxi              ###   ########.fr       */
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
	char	*var_val;
	t_environment	*current;

	var_val = NULL;
	current = shell->env_list;
	while(current != NULL)
	{
		if (ft_strcmp(current->env_var, var_name) == 0)
			return	(current->value);
		current = current->next_env_var;
	}
	return (var_val);
}

char	*expand_token(t_token *token, t_minishell *shell)
{
	int		i;
	int		var_start;
	char	*before;
	char	*after;
	char	*result;
	char	*new_result;
	char	*tmp;
	char	*var_name;
	char	*var_val;

	i = 0;
	var_start = 0;
	new_result = NULL;
	before = NULL;
	var_name = NULL;
	tmp = NULL;
	var_val = NULL;
	result = ft_strdup(token->token_val);
	if (!result)
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
	while (result[i])
	{
		if (result[i] == '$')
		{
			i += 1;
			var_start = i;
			while ((ft_isalnum(result[i])) || result[i] == '_')
				i++;	
			var_name = ft_substr(result, var_start, i - var_start);
			if (!var_name)
				display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
			var_val = ft_getenv(var_name, shell);
			if (!var_val)
				var_val = "";
			before = ft_substr(result, 0, var_start - 1);
			after = ft_strdup(result + i);
			tmp = ft_strjoin(before, var_val);
			new_result = ft_strjoin(tmp, after);
			free(var_name);
			free(before);
			free(after);
			free(tmp);
			free(result);
			result = new_result;
			i = 0;
		}
		else
			i++;
	}
	return (result);
}

char *def_expansion(t_token *token, t_minishell *shell)
{
	char	*commands;

	commands = NULL;
	if (find_dollar(token->token_val) == true && 
			(token->in_quotes == false || token->double_quoted == true))
	{
		printf("expanded\n");
		commands = expand_token(token, shell);
	}
	else
		commands = strdup(token->token_val);
	return (commands);
}