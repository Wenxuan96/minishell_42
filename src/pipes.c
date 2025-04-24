/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:59:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/24 15:34:26 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
//ls > temp.txt | grep txt < temp.txt | wc -l >> count.log


int create_pipes(t_minishell *shell)
{
	t_process   *process_lst;
	t_process   *current;
	// char *p1_cmd[] = {"ls", NULL};
	// char *p2_cmd[] = {"grep", "test", NULL};
	// char *p3_cmd[] = {"wc", "-l", NULL};

	char *p1_cmd[] = {"echo", "hello", NULL};
	char *p2_cmd[] = {"cat", NULL};
	char *p3_cmd[] = {"wc", "-c", NULL};


	// char *p1_cmd[] = {"ls", NULL};
	// char *p2_cmd[] = {"sort", NULL};
	// char *p3_cmd[] = {"head", "-n", "2", NULL};


	// char *p1_cmd[] = {"echo", "this is a test", NULL};
	// char *p2_cmd[] = {"grep", "test", NULL};
	// char *p3_cmd[] = {"wc", "-w", NULL};

	// char *p1_cmd[] = {"env", NULL};
	// // char *p1_cmd[] = {"export", "NEWVAR=hello", NULL};
	// char *p2_cmd[] = {"unset", "LC_TIME", NULL};
	// char *p3_cmd[] = {"wc", "-w", NULL};

	// int	p_num;
	// char	*buffer[30];

	// p_num = 0;
	process_lst = NULL;
	process_lst_add_back(new_process_lst(shell, p1_cmd), &process_lst);
	process_lst_add_back(new_process_lst(shell, p2_cmd), &process_lst);
	process_lst_add_back(new_process_lst(shell, p3_cmd), &process_lst);
	shell->process_list = process_lst;
	current = process_lst;
	while (current != NULL)
	{
		// printf("%s\n", current->command_arguments[0]);
		current = current->next_process;
		shell->num_processes++;
	}
	current = process_lst;
	if (shell->num_processes > 1)
	{
		while (current != NULL)
		{
			current->is_pipeline = 1;
			current = current->next_process;
		}
	}
	shell->pipes = allocate_pipes(shell->num_processes - 1);
	return (1);
	
}

int	assign_fd(t_minishell *shell)
{
	t_process	*current;
	int			i;

	current = shell->process_list;
	i = 0;
	while (current != NULL)
	{
		if (i == 0)
			current->input_fd = STDIN_FILENO;
		else
			current->input_fd = shell->pipes[i - 1][0];
		if (i == shell->num_processes - 1)
			current->output_fd = STDOUT_FILENO;
		else
			current->output_fd = shell->pipes[i][1];
		i++;
		current = current->next_process;
	}
	return (1);
}

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;
	char		*path;
	char		**env_vars;

	current = shell->process_list;
	shell->num_processes = 3;
	// printf("current node: %s\n", current->command_arguments[0]);
	while (current != NULL)
	{
		current->env_vars = copy_env_list(shell, current);
		pid = fork();
		if (pid < 0)
		{
			perror("Forking failed");
			return (0);	
		}
		else if(pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (current->is_builtin == 1 && shell->num_processes > 1)
			{
				execute_builtin(current, shell);
			}
			// printf("input_fd: %i\n", current->input_fd);
			// printf("output_fd: %i\n", current->output_fd);
			else
			{
				handle_redirection(current);
				dup2(current->input_fd, STDIN_FILENO);
				dup2(current->output_fd, STDOUT_FILENO);
				close_pipe_ends(shell, current);
				path = get_path(current);
				env_vars = execve_get_envvars(current);
				// printf_twod(env_vars);
				execve(path, current->command_arguments, env_vars);
			}
			close_pipe_ends(shell, current);
			exit(0);
		}
		else
		{
			if (current->is_builtin == 1 && shell->num_processes == 1)
				execute_builtin(current, shell);	
			current->pid = pid;
			current = current->next_process;
		}
	}
	close_pipe_ends_parent(shell);
	waitpid_children(shell);
	return (1);
}
