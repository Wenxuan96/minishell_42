/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:59:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/16 16:12:43 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ls > temp.txt | grep txt < temp.txt | wc -l >> count.log


int create_pipes(t_minishell *shell)
{
	t_process   *process_lst;
	t_process   *current;
	// char *p1_cmd[] = {"ls", NULL};
	// char *p2_cmd[] = {"grep", "txt", NULL};
	// char *p3_cmd[] = {"wc", "-l", NULL};

	// char *p1_cmd[] = {"echo", "this is a test", NULL};
	// char *p2_cmd[] = {"grep", "test", NULL};
	// char *p3_cmd[] = {"wc", "-w", NULL};

	char *p1_cmd[] = {"export", "NEWVAR=hello", NULL};
	char *p2_cmd[] = {"unset", "LC_TIME", NULL};
	char *p3_cmd[] = {"wc", "-w", NULL};

	int	p_num;
	char	*buffer[30];

	// p_num = 0;
	process_lst = NULL;
	process_lst_add_back(new_process_lst(shell, p1_cmd), &process_lst);
	process_lst_add_back(new_process_lst(shell, p2_cmd), &process_lst);
	process_lst_add_back(new_process_lst(shell, p3_cmd), &process_lst);
	shell->process_list = process_lst;
	current = process_lst;
	while (current != NULL)
	{
		printf("%s\n", current->command_arguments[0]);
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
	// int pipes[shell->num_processes - 1][2];
	// printf("num_processes: %num_cmd\n", shell->num_processes);
	
	// while (p_num < shell->num_processes - 1)
	// {
	// 	pipe(pipes[p_num]);
	// 	p_num++;
	// }
	shell->pipes = allocate_pipes(shell->num_processes - 1);
	// pipe(p);
	// write(p[1], "hello\n", 5);
	// read(p[0], buffer, 5);
	// write(STDOUT_FILENO, buffer, 5);
	p_num = 0;

	// write(pipes[0][1], "hello\n", 6);
	int	fd = open("test_file.txt", O_RDONLY);
	read(fd, buffer, 6);
	write(shell->pipes[0][1], buffer, 6);
	
	read(shell->pipes[0][0], buffer, 6);
	write(shell->pipes[1][1], buffer, 6);
	
	read(shell->pipes[1][0], buffer, 6);
	// write(STDOUT_FILENO, buffer, 6);
	close(fd);
	return (1);
	//create a dummy linked list with args
	//create n-1 pipes
	
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

void	print_fds(t_minishell *shell)
{
	t_process	*current;

	current = shell->process_list;
	while (current != NULL)
	{
		printf("\n\nProcess: %i\n", current->pid);
		printf("read end: %i\n", current->input_fd);
		printf("write end: %i\n\n", current->output_fd);
		current = current->next_process;
	}
}

void	close_pipe_ends(t_minishell *shell, t_process	*current)
{
	int	i;

	i = 0;
	while (i < shell->num_processes - 1)
	{
		if (shell->pipes[i][0] != current->input_fd)
			close(shell->pipes[i][0]);
		if (shell->pipes[i][1] != current->output_fd)
			close(shell->pipes[i][1]);
		i++;
	}
}

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;

	current = shell->process_list;
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
			// printf("input_fd: %i\n", current->input_fd);
			// printf("output_fd: %i\n", current->output_fd);
			dup2(current->input_fd, STDIN_FILENO);
			dup2(current->output_fd, STDOUT_FILENO);
			close_pipe_ends(shell, current);
			// sleep(1000);
			exit(0); 
		}
		else
		{
			current->pid = pid;
			// printf("\n\nprocess env var: %s\n", current->env_vars->env_var);
			// printf("process env var: %s\n\n", current->env_vars->value);
			// prt_env_lst(current->env_vars);
			// printf("Child PID: %d\n", current->pid);
			// printf("current node: %s\n", current->command_arguments[0]);
			current = current->next_process;
		}
	}
	waitpid_children(shell);
	// sleep(1000);
	return (1);
}


