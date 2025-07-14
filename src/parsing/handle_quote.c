/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:51:41 by wxi               #+#    #+#             */
/*   Updated: 2025/07/14 14:29:04 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_quotes(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && quote == '\0')
			quote = input[i];
		else if (input[i] == quote)
			quote = '\0';
		i++;
	}
	return (quote == '\0');
}

char	*handle_dollar_sign(char *trimmed)
{
	size_t	i;

	i = 0;
	while ((i < ft_strlen(trimmed))
		&& trimmed[i] && trimmed[i + 1] != '\0')
	{
		if (trimmed[i] == '\\' && trimmed[i + 1] == '\\')
		{
			while (i < ft_strlen(trimmed))
			{
				trimmed[i] = trimmed[i + 1];
				i++;
			}
			ft_printf("trimmed value is: %s\n", trimmed);
		}
		i++;
	}
	return (trimmed);
}

char	*remove_outer_quotes(char *sub)
{
	// size_t	len;
	// char	*trimmed;

	// len = ft_strlen(sub);
	// trimmed = NULL;
	// if ((sub[0] == '\"' && sub[len - 1] == '\"')
	// 	|| (sub[0] == '\'' && sub[len - 1] == '\''))
	// {
	// 	trimmed = ft_substr(sub, 1, len - 2);
	// 	if (!trimmed)
	// 		return (NULL);
	// 	if (sub[0] == '\"' && sub[len - 1] == '\"')
	// 	{
	// 		trimmed = handle_dollar_sign(trimmed);
	// 		if (!trimmed)
	// 			return (NULL);
	// 	}
	// 	return (trimmed);
	// }
	// return (sub);
	char	*result = malloc(strlen(sub) + 1);
	if (!result)
		return (NULL);

	size_t	i = 0;
	size_t	j = 0;
	char	quote = '\0';

	while (sub[i])
	{
		if ((sub[i] == '\'' || sub[i] == '"'))
		{
			if (quote == '\0') // open quote
				quote = sub[i];
			else if (quote == sub[i]) // close quote
				quote = '\0';
			else
				result[j++] = sub[i]; // inside other quote type
		}
		else
			result[j++] = sub[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
