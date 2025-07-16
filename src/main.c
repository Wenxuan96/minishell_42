/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:41:05 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/16 20:54:58 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "minishell.h"

int	run_heredoc(t_minishell *shell)
{
	t_process		*current;
	t_redirection	*redir;

	current = shell->process_list;
	while (current != NULL)
	{
		if (current->redirections)
		{
			redir = current->redirections;
			while (redir != NULL)
			{
				if (redir->type == HEREDOC)
					if (!handle_heredoc(current, redir, shell))
						return (0);
				redir = redir->next_redir;
			}
		}
		current = current->next_process;
	}
	return (1);
}

void	close_pipe_fds_only(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				fd;

	dir = opendir("/proc/self/fd");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name,
				"..") == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		fd = ft_atoi(entry->d_name);
		if (fd > 2 && fd < 1024)
			close(fd);
		entry = readdir(dir);
	}
	closedir(dir);
}

void	start_n_end_prcs(t_minishell *shell, t_process *p)
{
	create_processes(shell);
	set_process(*shell, &p);
	close_pipe_fds_only();
	ft_lstclear_process(&shell->process_list);
	if (shell->pipes)
		free_pipes(shell);
}

void	run_shell(int argc, t_minishell shell, t_process *p)
{
	while (1)
	{
		shell.exit_status = read_input(argc, &shell);
		if (shell.exit_status == EXEC_FAILURE)
			display_shell_error2(&shell, "lexer failed.", EXEC_FAILURE);
		if (shell.exit_status == 2)
			continue ;
		if (shell.exit_status == CMD_NOTFOUND)
		{
			display_shell_error2(&shell, "Command '' not found.", CMD_NOTFOUND);
			continue ;
		}
		set_process(shell, &p);
		create_pipes(&shell);
		assign_fd(&shell);
		if (!run_heredoc(&shell))
		{
			ft_lstclear_process(&shell.process_list);
			free_pipes(&shell);
			continue ;
		}
		start_n_end_prcs(&shell, p);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_process	*p;

	(void)argc;
	(void)argv;
	p = NULL;
	init_shell(&shell);
	setup_signals(0);
	create_env_lst(&shell.env_list, envp);
	run_shell(argc, shell, p);
	ft_exit(&shell, NULL);
	return (EXEC_SUCCESS);
}
