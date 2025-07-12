/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/07/12 14:31:02 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	row(char const *s, char c)
{
	int		i;
	int		nrow;
	int		add;

	i = 0;
	nrow = 0;
	add = 1;
	while (s[i])
	{
		if (s[i] != c && add == 1)
		{
			add = 0;
			nrow++;
		}
		if (s[i] == c && add == 0)
			add = 1;
		i++;
	}
	return (nrow);
}

static int	splitlen(char const *s, char c, int i)
{
	int		nlen;

	nlen = 0;
	while (s[i + nlen] != c && s[i + nlen] != '\0')
	{
		nlen++;
	}
	return (nlen);
}

static void	*freeall(char **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free (split[i]);
		i++;
	}
	free (split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	split = (char **)malloc((row(s, c) + 1) * sizeof (char *));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			split[j] = ft_substr(s, i, splitlen(s, c, i));
			if (!split[j])
				return (freeall(split, j));
			j++;
			i += splitlen(s, c, i);
		}
	}
	split[j] = NULL;
	return (split);
}
