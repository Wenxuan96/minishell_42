/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:14:48 by tignatov          #+#    #+#             */
/*   Updated: 2025/07/16 20:32:38 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <ctype.h>
# include <errno.h>
# include <parser.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>

struct							s_builtin;
typedef struct s_builtin		t_builtin;
extern volatile sig_atomic_t	g_exit_status;

# define EXEC_FAILURE 1
# define EXEC_SUCCESS 0
# define EX_BADUSAGE 2
# define EX_MISCERROR 2
# define EX_BINARY_FILE 126
# define EX_NOEXEC 126
# define EX_NOINPUT 126
# define CMD_NOTFOUND 127

typedef enum e_token_type
{
	WORD,
	REDIRECTION,
	PIPELINE,
	INIT,
}								t_token_type;

typedef enum e_redir_type
{
	OUTPUT,
	INPUT,
	HEREDOC,
	OUTPUT_APPEND,
	NONE,
}								t_redir_type;

typedef struct s_environment
{
	char						*env_var;
	char						*value;
	struct s_environment		*next_env_var;
}								t_environment;

typedef struct s_quote_context
{
	bool	has_quotes;
	bool	double_quoted;
	bool	single_quoted;
}	t_quote_context;

typedef struct s_token
{
	int							len;
	int							start;
	t_token_type				type;
	char						*token_val;
	bool						double_quoted;
	bool						in_quotes;
	struct s_token				*next_token;
}								t_token;

typedef struct s_redirection
{
	int							fd;
	t_redir_type				type;
	char						*file;
	struct s_redirection		*next_redir;
}								t_redirection;

typedef struct s_process
{
	pid_t						pid;
	char						**command_arguments;
	t_redirection				*redirections;
	t_environment				*env_vars;
	int							input_fd;
	int							output_fd;
	int							exit_status;
	bool						is_builtin;
	bool						is_pipeline;
	t_builtin					*builtin;
	int							completed;
	struct s_process			*next_process;
}								t_process;

typedef struct s_minishell
{
	char						*input_str;
	int							input_status;
	char						**heredoc_archive;
	int							heredoc_count;
	const char					**system_commands;
	const char					**buildin_commands;
	t_token						*token_list;
	t_process					*process_list;
	bool						in_quote;
	bool						heredoc_inquote;
	int							**pipes;
	int							exit_status;
	int							num_processes;
	int							orig_stdin;
	int							orig_stdout;
	t_environment				*env_list;
}								t_minishell;

t_environment					*ft_new_var_lst(char *variable, char *value);
void							ft_var_lstadd_back(t_environment **lst,
									t_environment *new);

int								create_env_lst(t_environment **env_list,
									char **envp);
t_environment					*copy_env_list(t_minishell *shell,
									t_process *process);

/*init*/
void							init_shell(t_minishell *shell);
t_process						*new_process_lst(t_minishell *shell,
									char **commands);
t_token							*new_token_lst(char *token);
void							set_process(t_minishell shell, t_process **p);

/*executor - processes/pipes*/
int								create_pipes(t_minishell *shell);
int								assign_fd(t_minishell *shell);
int								create_processes(t_minishell *shell);
int								read_input(int argc, t_minishell *shell);

/*executor*/
int								execute_builtin(t_process *process,
									t_minishell *shell);
int								execute_outside_cmd(t_process *process,
									t_minishell *shell);

/*executor - redirections*/
int								redirections(t_process *process_lst);
int								handle_redirection(t_process *process,
									t_minishell *shell);
int								handle_heredoc(t_process *current,
									t_redirection *curr_redir,
									t_minishell *shell);

/*executor - execve*/
char							**get_pathdirs(t_minishell *shell,
									t_process *process);
char							**get_path2(t_minishell *shell,
									t_process *process, int *found);
char							*get_path(t_minishell *shell,
									t_process *process);
char							**execve_get_envvars(t_minishell *shell);

/*cleanup*/
void							ft_lstclear_token(t_token **token_list);
void							ft_lstclear_env(t_environment **env_list);
void							ft_lstclear_redir(t_redirection **redir_list);
void							ft_lstclear_pr_envvars(t_process **process);
void							ft_lstclear_process(t_process **process_list);
void							ft_exit(t_minishell *shell, char *error_msg);
void							free_pipes(t_minishell *shell);
void							free_pipes2(int **pipes, int p_num);
void							free_2darray(char **arr);
void							free_everything(t_minishell *shell);
void							free_process(t_minishell *shell,
									t_process *current);
void							ft_clear_shell(t_minishell *shell);

/*utils_malloc*/
char							**allocate_array(char **commands);
int								**allocate_pipes(int p_num);
char							*ft_strjoin_heredoc(const char *s1,
									const char *s2);

/*utils_processes*/
void							process_lst_add_back(t_process *new_process,
									t_process **process_lst);
void							waitpid_children(t_minishell *shell);

/*utils_pipes*/
void							close_pipe_ends(t_minishell *shell,
									t_process *current);
void							close_pipe_ends_parent(t_minishell *shell);
void							close_pipe_fds_only(void);

/*utils_redir*/
t_redirection					*new_redir_lst(t_redir_type type, char *file);
void							redir_lst_add_back(t_redirection *new_redir,
									t_redirection **redir_lst);
int								handle_output(t_process *current,
									t_redirection *curr_redir);

int								handle_input(t_process *current,
									t_redirection *curr_redir);
int								handle_append(t_process *current,
									t_redirection *curr_redir);
int								free_heredoc(char *input_line,
									char *heredoc_buff, int *pipe_fd);
int								force_sigint(void);
int								setup_pipes(int *pipe_fd);

/*utils_builtins*/
void							prt_env_lst(t_environment *env_list);
int								parse_builtin(t_minishell *shell);

/*signals*/
int								setup_signals(int is_child);
int								setup_signals_heredoc(void);

/*testing*/
void							print_fds(t_minishell *shell);
void							printf_twod(char **arr);
void							prt_tokenlst(t_minishell *shell);

/*errors*/
void							display_shell_error(t_process *process,
									char *msg, int exit_status);
void							display_shell_error2(t_minishell *shell,
									char *msg, int exit_status);
void							exit_with_error(t_minishell *shell, char *msg,
									int exit_status);

size_t							count_dirs(char **dir_paths);
void							printf_twod_array(char **array);
char							**ft_split_env(char const *s, char c);
#endif
