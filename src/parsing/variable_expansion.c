/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:28:10 by wxi               #+#    #+#             */
/*   Updated: 2025/06/27 14:40:15 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_val(int *i, char *result, t_minishell *shell)
{
	char	*var_name;
	char	*var_val;
	int		var_len;

	var_name = NULL;
	var_val = NULL;
	var_len = 0;
	while (ft_isalnum(result[*i + var_len]) || result[*i + var_len] == '_')
		var_len++;
	var_name = ft_substr(result, *i, var_len);
	if (!var_name)
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
	var_val = ft_getenv(var_name, shell);
	free(var_name);
	if (!var_val)
		var_val = ft_strdup("");
	*i += var_len;
	return (var_val);
}

void	def_var_val(char *result, int *i, t_minishell *shell, char **var_val)
{
	if (result[*i] == '$')
	{
		*var_val = ft_itoa(getpid());
		(*i)++;
	}
	else if (result[*i] == '?')
	{
		if (g_exit_status == 0)
			*var_val = ft_itoa(shell->exit_status);
		else
			*var_val = ft_itoa(g_exit_status);
		(*i)++;
	}
	else if (result[*i] == '\0')
		*var_val = ft_strdup("$");
	else
		*var_val = expand_val(i, result, shell);
}

void	expand_result(char **result, int *i, char *tmp, t_minishell *shell)
{
	int		var_start;
	char	*before;
	char	*after;
	char	*new_result;
	char	*var_val;
	
	init_val(&var_start, &before, &after, &new_result);
	var_val = NULL;
	var_start = *i;
	(*i)++;
	def_var_val(*result, i, shell, &var_val);
	before = ft_substr(*result, 0, var_start);
	after = ft_strdup(*result + *i);
	tmp = ft_strjoin(before, var_val);
	new_result = ft_strjoin(tmp, after);
	free_var(before, after, tmp, *result);
	*result = new_result;
	*i = var_start + ft_strlen(var_val);
	if (var_val)
		free(var_val);
}

char	*expand_token(t_token *token, t_minishell *shell)
{
	int		i;
	char	*tmp;
	char	*var_val;
	char	*result;

	init_val(&i, &tmp, &result, &var_val);
	result = ft_strdup(token->token_val);
	if (!result)
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
	while (result[i])
	{
		if (result[i] == '$')
			expand_result(&result, &i, tmp, shell);
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
