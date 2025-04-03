/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:59:43 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/03 13:47:00 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ls | grep txt | wc -l


t_process	*new_process_lst(char **commands)
{
	t_process	*new_process;
	
	new_process = malloc(sizeof(t_process));
	new_process->command_arguments = commands;
	new_process->redirections= NULL;
	new_process->next_process= NULL;
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

int create_pipes(t_minishell *shell)
{
	t_process   *process_lst;
	char *p1_cmd[] = {"ls", NULL};
	char *p2_cmd[] = {"grep", "txt", NULL};
	char *p3_cmd[] = {"wc", "-l", NULL};
	int	p_num;
	char	*buffer[30];

	p_num = 0;
	process_lst = NULL;
	shell->process_list = process_lst;
	process_lst_add_back(new_process_lst(p1_cmd), &process_lst);
	process_lst_add_back(new_process_lst(p2_cmd), &process_lst);
	process_lst_add_back(new_process_lst(p3_cmd), &process_lst);
	while(process_lst != NULL)
	{
		// printf("%s\n", process_lst->command_arguments[0]);
		process_lst = process_lst->next_process;
		shell->num_processes++;
	}
	int pipes[shell->num_processes - 1][2];
	printf("num_processes: %i\n", shell->num_processes);
	
	while (p_num < shell->num_processes - 1)
	{
		pipe(pipes[p_num]);
		p_num++;
	}
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
	write(STDOUT_FILENO, buffer, 6);
	close(fd);
	return (1);
	//create a dummy linked list with args
	//create n-1 pipes
	
}

int	create_processes(t_minishell *shell)
{
	pid_t	pid;
	t_process   *current;

	current = shell->process_list;

	while (current != NULL)
	{
		pid = fork();
		if (pid < 0)
			perror("Forking failed");
			return (0);
		else
		
	}
}