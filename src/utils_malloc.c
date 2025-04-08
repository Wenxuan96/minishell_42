/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:18:04 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/07 14:57:55 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_array(char **commands)
{
	char	**malloced_array;
	int	num_cmd;
	int	i;

	num_cmd = 0;
	i = 0;
	while (commands[num_cmd])
		num_cmd++;
	
	malloced_array = (char **)malloc(num_cmd * sizeof(char *));
	while (i < num_cmd)
	{
		malloced_array[i] = (char *)malloc(ft_strlen(commands[i]));
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

	i = 0;
	pipes = (int **)malloc(p_num * sizeof(int *));
	while (i < p_num)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		pipe(pipes[i]);
		i++;
	}

	return (pipes);
}
