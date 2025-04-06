/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:59:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/06 17:01:26 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ls | grep txt | wc -l


int create_pipes(t_minishell *shell)
{
	t_process   *process_lst;
	t_process   *current;
	char *p1_cmd[] = {"ls", NULL};
	char *p2_cmd[] = {"grep", "txt", NULL};
	char *p3_cmd[] = {"wc", "-l", NULL};
	int	p_num;
	char	*buffer[30];

	p_num = 0;
	process_lst = NULL;
	process_lst_add_back(new_process_lst(p1_cmd), &process_lst);
	process_lst_add_back(new_process_lst(p2_cmd), &process_lst);
	process_lst_add_back(new_process_lst(p3_cmd), &process_lst);
	shell->process_list = process_lst;
	current = process_lst;
	while(current != NULL)
	{
		printf("%s\n", current->command_arguments[0]);
		current = current->next_process;
		shell->num_processes++;
	}
	int pipes[shell->num_processes - 1][2];
	// printf("num_processes: %num_cmd\n", shell->num_processes);
	
	while (p_num < shell->num_processes - 1)
	{
		pipe(pipes[p_num]);
		p_num++;
	}
	shell->pipes = allocate_pipes(p_num);
	// pipe(p);
	// write(p[1], "hello\n", 5);
	// read(p[0], buffer, 5);
	// write(STDOUT_FILENO, buffer, 5);
	p_num = 0;

	// write(pipes[0][1], "hello\n", 6);
	int	fd = open("test_file.txt", O_RDONLY);
	read(fd, buffer, 6);
	write(pipes[0][1], buffer, 6);
	
	read(pipes[0][0], buffer, 6);
	write(pipes[1][1], buffer, 6);
	
	read(pipes[1][0], buffer, 6);
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
		if (i == shell->num_processes)
			current->output_fd = STDOUT_FILENO;
		else
			current->output_fd = shell->pipes[i - 1][1];
		i++;
		current = current->next_process;
	}
	return (1);
}

int	create_processes(t_minishell *shell)
{
	pid_t		pid;
	t_process	*current;

	current = shell->process_list;
	// printf("current node: %s\n", current->command_arguments[0]);
	while (current != NULL)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Forking failed");
			return (0);	
		}
		else if(pid == 0)
		{
			printf("I am child PID: %d\n", getpid());
			// sleep(1000);
			exit(0);
		}
		else
		{
			current->pid = pid;
			printf("Child PID: %d\n", current->pid);
			printf("current node: %s\n", current->command_arguments[0]);
			current = current->next_process;
		}
	}
	waitpid_children(shell);
	// sleep(1000);
	return (1);
}


