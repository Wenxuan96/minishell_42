/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/02/23 21:10:33 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int		i;
// 	char	cchar;

// 	if (s == NULL)
// 		return (NULL);
// 	i = 0;
// 	cchar = (char)c;
// 	while (s[i])
// 	{
// 		if (s[i] == cchar)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (s[i] == cchar)
// 		return ((char *)&s[i]);
// 	return (NULL);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*ptr;
// 	int		i;

// 	i = 0;
// 	ptr = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
// 	if (!ptr)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		ptr[i] = s[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!str)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	return (str);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	char	*sub;

// 	i = 0;
// 	if (ft_strlen(s) == 0 || start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (ft_strlen(s) < start + len)
// 		len = ft_strlen(s) - start;
// 	sub = (char *)malloc(len + 1);
// 	if (!sub)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		sub[i] = s[start + i];
// 		i++;
// 	}
// 	sub[i] = '\0';
// 	return (sub);
// }
