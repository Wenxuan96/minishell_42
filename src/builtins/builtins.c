/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:09:16 by tignatov          #+#    #+#             */
/*   Updated: 2025/06/06 17:29:23 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

/*
	echo
	pwd
	cd
	export
	unset
	env
	exit
*/

t_builtin	*new_builtin(t_builtin_type type, builtin_func *function)
{
	t_builtin	*new_builtin;

	new_builtin = malloc(sizeof(t_builtin));
	new_builtin->type = type;
	new_builtin->function = function;
	return (new_builtin);
}

int	assign_builtin(t_process *process, t_builtin_type type, builtin_func *function)
{
	t_process	*current;

	current = process;
	current->builtin = new_builtin(type, function);
	if (!current->builtin)
		return (0);
	current->is_builtin = 1;
	return (1);
}

int	is_builtin(t_minishell *shell, t_process *process)
{
	char		*command;
	const char	**builtins;
	int			i;
	
	// printf("command: %s\n", process->command_arguments[0]);
	command = process->command_arguments[0];
	builtins = shell->buildin_commands;
	i = 0;  
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(builtins[i], command) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	parse_builtin(t_minishell *shell)
{
	t_process	*current;
	int			assign_error;
 
	current = shell->process_list;
	while (current != NULL && current->command_arguments[0] != NULL)
	{
		if (is_builtin(shell, current))
		{
			if (ft_strcmp(current->command_arguments[0], "cd") == 0)
				assign_error = assign_builtin(current, CD, cd_builtin);
			else if (ft_strcmp(current->command_arguments[0], "echo") == 0)
				assign_error = assign_builtin(current, ECHO, echo_builtin);
			else if (ft_strcmp(current->command_arguments[0], "env") == 0)
				assign_error = assign_builtin(current, ENV, env_builtin);
			else if (ft_strcmp(current->command_arguments[0], "exit") == 0)
				assign_error = assign_builtin(current, EXIT, exit_builtin);
			else if (ft_strcmp(current->command_arguments[0], "export") == 0)
				assign_error = assign_builtin(current, EXPORT, export_builtin);
			else if (ft_strcmp(current->command_arguments[0], "pwd") == 0)
				assign_error = assign_builtin(current, PWD, pwd_builtin);
			else if (ft_strcmp(current->command_arguments[0], "unset") == 0)
				assign_error = assign_builtin(current, UNSET, unset_builtin);
			if (assign_error == 0)
				display_shell_error(current, "memory allocation failed", EXEC_FAILURE);
		}
		current = current->next_process;
	}
	return (1);
}
