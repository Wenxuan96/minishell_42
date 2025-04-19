/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:33 by wxi               #+#    #+#             */
/*   Updated: 2025/04/19 19:58:39 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void rearrange_input_arr(char **input_arr, int i)
// {
// 	int	j;

// 	j = i + 1;
// 	while (input_arr[j])
// 	{
// 		input_arr[j] = input_arr[j + 1];
// 		j++;
// 	}
// 	input_arr[j] = NULL;
// }

// int	single_quo_counter(char *input_str1, char *input_str2)
// {
// 	int			i;
// 	static int	n;

// 	n = 0;
// 	i = 0;
// 	while (input_str1[i])
// 	{
// 		if (input_str1[i++] == '\'')
// 			n++;
// 	}
// 	i = 0;
// 	while (input_str2[i])
// 	{
// 		if (input_str2[i++] == '\'')
// 			n++;
// 	}
// 	return (n);
// }

// int	double_quo_counter(char *input_str1, char *input_str2)
// {
// 	int			i;
// 	static int	n;

// 	n = 0;
// 	i = 0;
// 	while (input_str1[i])
// 	{
// 		if (input_str1[i++] == '\"')
// 			n++;
// 	}
// 	i = 0;
// 	while (input_str2[i])
// 	{
// 		if (input_str2[i++] == '\"')
// 			n++;
// 	}
// 	return (n);
// }

// int	find_closed_quote(char *input_str1, char *input_str2)
// {
// 	int	n_double_quo;
// 	int	n_single_quo;

// 	n_double_quo = double_quo_counter(input_str1, input_str2);
// 	n_single_quo = single_quo_counter(input_str1, input_str2);
// 	if ((n_double_quo > 0) && (n_double_quo % 2 == 0) && (n_single_quo == 0))
// 		return (1);
// 	if ((n_double_quo == 0) && (n_single_quo > 0) && (n_single_quo % 2 == 0))
// 		return (1);
// 	if (n_double_quo > 0 && n_single_quo > 0)
// 	{
		
// 	}
// 	return (0);
// }

void	handle_slash(char *input_str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input_str[i])
	{
		// Open/close quotes
		if (input_str[i] == '\'' && quote == 0)
			quote = '\'';
		else if (input_str[i] == '"' && quote == 0)
			quote = '"';
		else if ((input_str[i] == '\'' && quote == '\'') || (input_str[i] == '"' && quote == '"'))
			quote = 0;
		// Handle backslash
		else if (input_str[i] == '\\')
		{
			if (quote == '"')
			{
				if (input_str[i + 1] == '"' || input_str[i + 1] == '\\' || input_str[i + 1] == '$' || input_str[i + 1] == '`')
					memmove(&input_str[i], &input_str[i + 1], ft_strlen(&input_str[i + 1]) + 1);
				else
					i++;
			}
			else if (quote == 0)
				memmove(&input_str[i], &input_str[i + 1], ft_strlen(&input_str[i + 1]) + 1);
			else
				i++;
		}
		else
			i++;
	}
}

int	quote_manager(t_minishell *shell)
{
	int		i;
	char	*new_str;

	i = 0;
	handle_slash(shell->input_str);
/* step1: loop trough the whole str
step2: assign value to the token directly if no close quote is found, otherwise assign the value by space*/
	return (EXIT_SUCCESS);
}