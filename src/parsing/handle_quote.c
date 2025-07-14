/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:51:41 by wxi               #+#    #+#             */
/*   Updated: 2025/07/14 16:30:30 by wxi              ###   ########.fr       */
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

void	quote_removal_loop(const char *sub, char *result)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	while (sub[i])
	{
		if (sub[i] == '\'' || sub[i] == '"')
		{
			if (quote == '\0')
				quote = sub[i];
			else if (quote == sub[i])
				quote = '\0';
			else
				result[j++] = sub[i];
		}
		else
			result[j++] = sub[i];
		i++;
	}
	result[j] = '\0';
}

char	*remove_outer_quotes(char *sub)
{
	char	*result;

	result = malloc(strlen(sub) + 1);
	if (!result)
		return (NULL);
	quote_removal_loop(sub, result);
	return (result);
}
