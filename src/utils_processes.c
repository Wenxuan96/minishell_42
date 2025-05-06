/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:19:04 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/05 11:50:40 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_environment	*copy_env_list(t_minishell *shell, t_process *process);

t_process	*new_process_lst(t_minishell *shell, char **commands)
{
	t_process	*new_process;
	(void)shell;
	new_process = malloc(sizeof(t_process));
	new_process->command_arguments = allocate_array(commands);
	new_process->redirections= NULL;
	new_process->env_vars = NULL;
	new_process->input_fd = -2;
	new_process->output_fd = -2;
	new_process->next_process= NULL;
	new_process->is_builtin = 0;
	new_process->is_pipeline = -1;
	new_process->builtin = NULL;
	new_process->completed = 0;
	return (new_process);
}

void	process_lst_add_back(t_process   *new_process, t_process   **process_lst)
{
	t_process	*current;
	if (*process_lst == NULL)
	{
		*process_lst = new_process;
		return ;
	}
	current = *process_lst;
	while (current->next_process != NULL)
		current = current->next_process;
	current->next_process = new_process;
}

void	waitpid_children(t_minishell *shell)
{
    t_process *current_process;
    int wait_res;
	int	status;
    
    current_process = shell->process_list;
    while (current_process != NULL)
    {
        wait_res = waitpid(current_process->pid, &status, 0);
        if (wait_res == -1)
			exit_with_error(shell, "waitpid() failed", EXEC_FAILURE);
		if (current_process->next_process == NULL)
        {
            if (WIFEXITED(status))
                g_exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_exit_status = 128 + WTERMSIG(status);
        }
        current_process = current_process->next_process;
    }
}

// t_environment	*copy_env_list(t_minishell *shell, t_process *process)
// {
// 	t_environment	*current;
// 	t_environment	*new_env_lst;
// 	t_environment	*new_env_node;
// 	char			*variable;
// 	char			*value;

// 	new_env_lst = NULL;
// 	current = shell->env_list;
// 	while (current != NULL)
// 	{
// 		variable = ft_strdup(current->env_var);
// 		if (current->value)
// 			value = ft_strdup(current->value);
// 		if (!variable || !value)
// 			exit_with_error(shell, "memory allocation failed", EXEC_FAILURE);
// 		else
// 			value = NULL;
// 		new_env_node = ft_new_var_lst(variable, value);
// 		ft_var_lstadd_back(&new_env_lst, new_env_node);
// 		current = current->next_env_var;
// 	}
// 	process->env_vars = new_env_lst;
// 	// printf("\n\nprocess env var: %s\n", process->env_vars->env_var);
// 	return (process->env_vars);
// }

