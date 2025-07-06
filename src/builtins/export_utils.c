/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:28:27 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/06 17:28:33 by tignatov         ###   ########.fr       */
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
	{
		split = (char **)malloc((2 + 1) * sizeof(char *));
		split[0] = ft_substr(s, 0, i);
		split[1] = ft_strdup("");
		split[2] = NULL;
		return (split);
	}
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
		trimmed_str = ft_substr(str, 0, len - 1);
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
