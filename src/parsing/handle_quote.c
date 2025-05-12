/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:51:41 by wxi               #+#    #+#             */
/*   Updated: 2025/05/11 16:17:12 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validate_quotes(const char *input)
{
	int		i;
	char 	quote;
	
	i = 0;
	quote = '\0';
	while(input[i])
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
	while (trimmed[i] && trimmed[i + 1] != '\0')
	{
		if (trimmed[i] == '\\' && trimmed[i + 1] == '$')
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
	return(trimmed);
}

// Helper to remove surrounding quotes if they match
char	*remove_outer_quotes(char *str)
{
	size_t	len;
	char	*trimmed;

	len = ft_strlen(str);
	if ((str[0] == '\"' && str[len - 1] == '\"') ||
		(str[0] == '\'' && str[len - 1] == '\''))
	{
		trimmed = ft_substr(str, 1, len - 2);
		if (str[0] == '\"' && str[len - 1] == '\"')
			trimmed = handle_dollar_sign(trimmed);
		// free(str);
		return (trimmed);
	}
	return (str);
}
