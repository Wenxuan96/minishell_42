/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_get_path_utls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:42 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/07 17:43:27 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*build_path(char *dir, char *command)
{
	size_t	command_len;
	size_t	total_path_len;
	size_t	dir_path_len;
	char	*path;

	command_len = ft_strlen(command);
	dir_path_len = ft_strlen(dir);
	total_path_len = dir_path_len + command_len + 2;
	path = (char *)malloc(total_path_len);
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, total_path_len);
	ft_strlcat(path, "/", total_path_len);
	ft_strlcat(path, command, total_path_len);
	return (path);
}

char	**concat_path(t_minishell *shell, char **dir_paths, char *command)
{
	char	**new_dir_path;
	size_t	num_dirs;
	size_t	i;

	new_dir_path = NULL;
	num_dirs = count_dirs(dir_paths);
	i = 0;
	new_dir_path = (char **)malloc((num_dirs + 1) * sizeof(char *));
	if (!new_dir_path)
		display_shell_error2(shell, "memory allocation failed", EXEC_FAILURE);
	while (i < num_dirs)
	{
		new_dir_path[i] = build_path(dir_paths[i], command);
		if (!new_dir_path[i])
		{
			free_2darray(new_dir_path);
			display_shell_error2(shell, "memory allocation failed",
				EXEC_FAILURE);
			return (NULL);
		}
		i++;
	}
	new_dir_path[i] = NULL;
	return (new_dir_path);
}

char	**get_path2(t_minishell *shell, t_process *process, int *found)
{
	t_environment	*current;
	char			**dir_paths;

	*found = 0;
	current = shell->env_list;
	dir_paths = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_var, "PATH") == 0)
		{
			*found = 1;
			dir_paths = ft_split(current->value, ':');
			if (!dir_paths)
			{
				display_shell_error(process, "memory allocation failed",
					EXEC_FAILURE);
				return (NULL);
			}
			break ;
		}
		current = current->next_env_var;
	}
	return (dir_paths);
}

char	**get_pathdirs(t_minishell *shell, t_process *process)
{
	char	**dir_paths;
	char	**new_dir_paths;
	int		found;

	dir_paths = NULL;
	new_dir_paths = NULL;
	found = 0;
	dir_paths = get_path2(shell, process, &found);
	if (!dir_paths)
		return (NULL);
	if (found == 0)
		return (display_shell_error(process, "No such file or directory",
				CMD_NOTFOUND), NULL);
	new_dir_paths = concat_path(shell, dir_paths,
			process->command_arguments[0]);
	free_2darray(dir_paths);
	return (new_dir_paths);
}
