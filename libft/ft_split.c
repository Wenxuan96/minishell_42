/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/04/17 16:12:27 by tignatov         ###   ########.fr       */
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
	if (!split || !s)
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

// int	main(void)
// {	
// 	char	tabstr[] = "aaaaaaaaa aaaaaaa";
// 	char **splitstrs;
// 	int		i;
// 	i = 0;
// 	splitstrs = ft_split(tabstr, ' ');
// 	while (splitstrs[i])
// 	{
// 		printf("%p: %s\n", &splitstrs[i], splitstrs[i]);
// 		i++;
// 	}
// }



// static char	*ft_strncpy(char *dst, const char *src, size_t n)
// {
// 	size_t	i;

// 	if (dst == NULL || src == NULL || n == 0)
// 		return (dst);
// 	i = 0;
// 	while (src[i] != '\0' && i < n)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		dst[i] = '\0';
// 		i++;
// 	}
// 	return (dst);
// }

// static int	ft_count_substrings(const char *s, char c)
// {
// 	int	i;
// 	int	count;
// 	int	in_substring;

// 	i = 0;
// 	count = 0;
// 	in_substring = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != c && !in_substring)
// 		{
// 			in_substring = 1;
// 			count++;
// 		}
// 		else if (s[i] == c)
// 			in_substring = 0;
// 		i++;
// 	}
// 	return (count);
// }

// static void	ft_free_arr(char **arr, int k)
// {
// 	int	j;

// 	j = 0;
// 	while (j < k)
// 	{
// 		free(arr[j]);
// 		j++;
// 	}
// 	free(arr);
// }

// static char	*ft_words(char const *s, char c, int *i)
// {
// 	int		start;
// 	char	*word;

// 	while (s[*i] == c)
// 		(*i)++;
// 	start = *i;
// 	while (s[*i] != c && s[*i] != '\0')
// 		(*i)++;
// 	word = (char *)malloc((*i - start + 1) * sizeof(char));
// 	if (!word)
// 		return (NULL);
// 	ft_strncpy(word, &s[start], (size_t)(*i - start));
// 	word[*i - start] = '\0';
// 	return (word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;
// 	int		i;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	arr = (char **)malloc((ft_count_substrings(s, c) + 1) * sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	while (k < ft_count_substrings(s, c))
// 	{
// 		arr[k] = ft_words(s, c, &i);
// 		if (!arr[k])
// 		{
// 			ft_free_arr(arr, k);
// 			return (NULL);
// 		}
// 		k++;
// 	}
// 	arr[k] = NULL;
// 	return (arr);
// }
