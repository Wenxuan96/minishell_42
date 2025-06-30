/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:54 by tignatov          #+#    #+#             */
/*   Updated: 2025/06/30 08:37:44 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/*void    print_env(t_environment   *env_list)
{
	while (env_list)
	{
		printf("%s=", env_list->env_var);
		printf("%s\n", env_list->value);
		env_list = env_list->next_env_var;
	}
}*/
int	validate_cd_args(t_process *process)
{
	if (process->command_arguments[1] != NULL
		&& process->command_arguments[2] != NULL)
		display_shell_error(process, "cd: too many arguments", EXEC_FAILURE);
	return (0);
}

char	*get_cd_path(t_process *process, t_minishell *shell)
{
	t_environment	*env_list;
	char			*path;

	path = NULL;
	if (process->command_arguments[1] == NULL
		|| ft_strcmp(process->command_arguments[1], "--") == 0)
	{
		env_list = shell->env_list;
		while (env_list != NULL)
		{
			if (ft_strcmp(env_list->env_var, "HOME") == 0)
			{
				path = env_list->value;
				break ;
			}
			env_list = env_list->next_env_var;
		}
		if (!path)
			return (display_shell_error(process, "cd: HOME does not exist",
					EXEC_FAILURE), NULL);
	}
	else
		path = process->command_arguments[1];
	return (path);
}

int	change_dir(t_process *process, char *path)
{
	if (chdir(path) == -1)
	{
		if (errno == ENOENT)
			return (display_shell_error(process,
					"cd: no such file or directory", EXEC_FAILURE), 0);
		else if (errno == EACCES)
			return (display_shell_error(process, "cd: permission denied",
					EXEC_FAILURE), 0);
		else if (errno == ENOTDIR)
			return (display_shell_error(process, "cd: not a directory",
					EXEC_FAILURE), 0);
		else
			return (display_shell_error(process, "cd: error", EXEC_FAILURE), 0);
	}
	return (1);
}

int	update_pwd(t_process *process, t_minishell *shell)
{
	char			*new_path_buffer;
	int				len;
	t_environment	*env;

	new_path_buffer = getcwd(NULL, 0);
	if (!new_path_buffer)
		return (display_shell_error(process, "cd: getcwd failed", EXEC_FAILURE),
			0);
	env = shell->env_list;
	while (env != NULL)
	{
		len = ft_strlen(env->env_var);
		if (ft_strncmp(env->env_var, "PWD", len) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_path_buffer);
			if (!env->value)
				return (free(new_path_buffer), display_shell_error(process,
						"cd: memory allocation failed", EXEC_FAILURE), 0);
			break ;
		}
		env = env->next_env_var;
	}
	free(new_path_buffer);
	return (1);
}

int	cd_builtin(t_process *process, t_minishell *shell)
{
	char	*path;
	int		status;

	path = NULL;
	status = validate_cd_args(process);
	path = get_cd_path(process, shell);
	if (!path)
		return (0);
	status = change_dir(process, path);
	status = update_pwd(process, shell);
	return (status);
}
