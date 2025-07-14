/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:07:55 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/13 13:58:59 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	pwd_builtin(t_process *process, t_minishell *shell)
{
	char	*path_buffer;

	(void)process;
	(void)shell;
	path_buffer = getcwd(NULL, 0);
	if (!path_buffer)
	{
		display_shell_error(process, "pwd: getcwd failed", EXEC_FAILURE);
		return (0);
	}
	write(STDOUT_FILENO, path_buffer, ft_strlen(path_buffer));
	write(STDOUT_FILENO, "\n", 1);
	free(path_buffer);
	return (1);
}
