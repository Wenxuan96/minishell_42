/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_get_path_utls2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:42 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 17:32:00 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	printf_twod_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	printf("\n\n");
}

size_t	count_dirs(char **dir_paths)
{
	size_t	num_dirs;

	num_dirs = 0;
	while (dir_paths[num_dirs] != NULL)
		num_dirs++;
	return (num_dirs);
}
