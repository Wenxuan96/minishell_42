/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:26:48 by wxi               #+#    #+#             */
/*   Updated: 2025/05/21 09:22:33 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	skip_whitespace(const char *str, int *i)
// {
// 	while (str[*i] == ' ' || str[*i] == '\t')
// 		(*i)++;
// }

void	def_token(t_minishell *shell, int t_len, int t_start)
{
	t_token	*new_token;
	char	*sub;
	
	sub = ft_substr(shell->input_str, t_start, t_len);
	if (!sub || sub[0] == '\0') // <- 🔥 important check
		return (free(sub), (void)0);
	new_token = new_token_lst(sub);
	new_token->len = t_len;
	new_token->start = t_start;
	new_token->type = token_checker(new_token->token_val);
	if (((sub[0] == '\"' && sub[ft_strlen(sub) - 1] == '\"') ||
		(sub[0] == '\'' && sub[ft_strlen(sub) - 1] == '\'')))
	{
		new_token->in_quotes = true;
		free(new_token->token_val);
		new_token->token_val = NULL;
		new_token->token_val = remove_outer_quotes(sub);
	}
	else
		new_token->in_quotes = false;
	new_token->next_token = NULL;
	free(sub);
	ms_token_add_back(&shell->token_list, new_token);
}

void	def_special_token(t_minishell *shell, int *i)
{
	if (ft_strncmp(shell->input_str + *i, "<<", 2) == 0
		|| ft_strncmp(shell->input_str + *i, ">>", 2) == 0)
	{
		def_token(shell, 2, *i);
		(*i) += 2;
	}
	else if (ft_strchr("|<>", shell->input_str[*i]) != NULL)
	{
		def_token(shell, 1, *i);
		(*i)++;
	}
}

void	iter_input_str(t_minishell *shell, int i, int start, char quote_char)
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
				def_token(shell, i - start, start);
			while (shell->input_str[i] == ' ' || shell->input_str[i] == '\t')
				i++;
			while (ft_strchr("|<>", shell->input_str[i]) != NULL)
				def_special_token(shell, &i);
			start = i;
			continue;
		}
		i++;
	}
	if (i != start)
		def_token(shell, i - start, start);
}

void tokenize_input(t_minishell *shell)
{
	int		i;
	int		start;
	char	quote_char;

	i = 0;
	start = 0;
	quote_char = '\0';
	if (!validate_quotes(shell->input_str))
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return;
	}
	iter_input_str(shell, i, start, quote_char);
}
