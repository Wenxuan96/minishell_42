/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:18:04 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/08 14:53:51 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_array(char **commands)
{
	char	**malloced_array;
	int		num_cmd;
	int		i;

	num_cmd = 0;
	i = 0;
	while (commands[num_cmd])
		num_cmd++;
	malloced_array = (char **)malloc((num_cmd + 1) * sizeof(char *));
	if (!malloced_array)
		return (NULL);
	while (i < num_cmd)
	{
		malloced_array[i] = (char *)malloc(ft_strlen(commands[i]) + 1);
		if (!malloced_array[i])
			return (free_2darray(malloced_array), NULL);
		ft_strlcpy(malloced_array[i], commands[i], ft_strlen(commands[i]) + 1);
		i++;
	}
	malloced_array[i] = NULL;
	return (malloced_array);
}

int	**allocate_pipes(int p_num)
{
	int	**pipes;
	int	i;
	int	num_pipes;

	i = 0;
	num_pipes = p_num;
	pipes = (int **)malloc(p_num * sizeof(int *));
	if (!pipes)
		return (0);
	while (i < p_num)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
			return (free_pipes2(pipes, num_pipes), NULL);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

char	*ft_strjoin_heredoc(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\n';
	i++;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
