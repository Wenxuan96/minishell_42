/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:26:48 by wxi               #+#    #+#             */
/*   Updated: 2025/05/29 12:08:41 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	def_token(t_minishell *shell, int t_len, int t_start)
{
	t_token	*new_token;
	char	*sub;

	sub = ft_substr(shell->input_str, t_start, t_len);
	if (!sub || sub[0] == '\0') // <- 🔥 important check
		return (free(sub), 0);
	new_token = new_token_lst(sub);
	if (!new_token)
		return (free(sub), 0);
	new_token->len = t_len;
	new_token->start = t_start;
	new_token->type = token_checker(new_token->token_val);
	if (!def_in_quotes(sub[0], sub[ft_strlen(sub) - 1], new_token, sub))
		return (free(sub), 0);
	new_token->next_token = NULL;
	/* if double_quoted is true then expand */
	if (new_token->double_quoted == true)
	{
		ft_printf("double quote_detected\n");
	}
	free(sub);
	ms_token_add_back(&shell->token_list, new_token);
	return (1);
}

int	def_special_token(t_minishell *shell, int *i)
{
	if (ft_strncmp(shell->input_str + *i, "<<", 2) == 0
		|| ft_strncmp(shell->input_str + *i, ">>", 2) == 0)
	{
		if (!def_token(shell, 2, *i))
			return (0);
		(*i) += 2;
	}
	else if (ft_strchr("|<>", shell->input_str[*i]) != NULL)
	{
		if (!def_token(shell, 1, *i))
			return (0);
		(*i)++;
	}
	return (1);
}

int	iter_input_str(t_minishell *shell, int i, int start, char quote_char)
{
	while (shell->input_str[i])
	{
		if ((quote_char == '\0') && (shell->input_str[i] == '\''
			|| shell->input_str[i] == '\"'))//check if it is in-quote
			quote_char = shell->input_str[i];
		else if (quote_char != '\0' && shell->input_str[i] == quote_char)
			quote_char = '\0';//check if a quote is closed
		else if (quote_char == '\0' && (ft_strchr(" \t|<>", shell->input_str[i]) != NULL))
		{
			if (i != start)// to define the token before it hits a special character
			{
				if (!def_token(shell, i - start, start))
					return (0);
			}
			while (shell->input_str[i] == ' ' || shell->input_str[i] == '\t')
				i++;
			while (ft_strchr("|<>", shell->input_str[i]) != NULL)
			{
				if (!def_special_token(shell, &i))
					return (0);
			}
			start = i;
			continue;
		}
		i++;
	}
	if (i != start)
	{
		if (!def_token(shell, i - start, start))
			return (0);
	}
	return (1);
}

int tokenize_input(t_minishell *shell)
{
	int		i;
	int		start;
	char	quote_char;

	i = 0;
	start = 0;
	quote_char = '\0';
	if (!validate_quotes(shell->input_str))
	{
		display_shell_error2(shell, "minishell: syntax error: unclosed quote", 2);
		return (0);
	}
	if (!iter_input_str(shell, i, start, quote_char))
	{
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
		return (0);
	}
	// def_expansion(shell->token_list);
	return (1);
}
