/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_get_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:42 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 16:14:41 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*find_absolute_path(t_process *process)
{
	struct stat	path_stat;

	if (access(process->command_arguments[0], X_OK) != 0)
	{
		if (errno == ENOTDIR)
			display_shell_error(process, "Not a directory", EX_NOEXEC);
		else if (errno == ENOENT)
			display_shell_error(process, "No such file or directory",
				EX_NOEXEC);
		else if (errno == EACCES)
			display_shell_error(process, "Permission is denied", EX_NOEXEC);
		return (NULL);
	}
	if (stat(process->command_arguments[0], &path_stat) != 0)
	{
		display_shell_error(process, "stat() failed", EX_NOEXEC);
		return (NULL);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		display_shell_error(process, "Is a directory", CMD_NOTFOUND);
		return (NULL);
	}
	return (ft_strdup(process->command_arguments[0]));
}

char	*search_inpaths(t_minishell *shell, t_process *process)
{
	int		i;
	char	**path_dirs;
	char	*path;

	path = NULL;
	path_dirs = get_pathdirs(shell, process);
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i] != NULL)
	{
		if (access(path_dirs[i], X_OK) == 0)
		{
			path = ft_strdup(path_dirs[i]);
			if (!path)
			{
				free_2darray(path_dirs);
				return (display_shell_error(process, "memory allocation failed",
						EXEC_FAILURE), NULL);
			}
			break ;
		}
		i++;
	}
	return (free_2darray(path_dirs), path);
}

char	*get_path(t_minishell *shell, t_process *process)
{
	char	*path;

	path = NULL;
	if (ft_strchr(process->command_arguments[0], '/'))
		return (find_absolute_path(process));
	path = search_inpaths(shell, process);
	if (!path)
		return (display_shell_error(process, "command not found", CMD_NOTFOUND),
			NULL);
	return (path);
}
