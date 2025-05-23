#ifndef MINISHELL_H
# define MINISHELL_H
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft.h"
#include <sys/wait.h>
#include <parser.h>

struct s_builtin;
typedef struct s_builtin t_builtin;
extern volatile sig_atomic_t g_exit_status;
// typedef struct	s_environment	t_environment;

/*
Lexer: takes in an input line
output: array of tokens
*/
typedef	enum	e_token_type
{
	WORD,
	REDIRECTION,
	PIPELINE,
	INIT,
}	t_token_type;

typedef	enum	e_redir_type
{
	OUTPUT,                 /*  >   */
	INPUT,                  /*  <   */
	HEREDOC,                /*  <<   */
	OUTPUT_APPEND,          /*  >>   */
	NONE,
}	t_redir_type;

typedef	enum e_exit_status
{
	MS_EXIT_FAILURE = 1,
	MS_EXIT_SUCCESS = 0,
	MS_TARGET_NOT_FOUND = 127,
}	t_exit_status;

typedef struct	s_environment
{
	char					*env_var;
	char					*value;
	struct	s_environment	*next_env_var;
} t_environment;

typedef struct s_token
{
	int				len;
	int				start;
	t_token_type	type;
	char			*token_val;
	bool			in_quotes;  /* Indicates if the token was enclosed in quotes (if not in_quotes, give an error)*/
	struct s_token	*next_token;
}	t_token;

/*
Parser: takes in an array of tokens
output: linked list of structs
1. group tokens by pipes into linked list
2. expansions ($HOME etc)
3. go through linked list and look for words -> they become arguments to execute
	also checking the syntaxis
*/

typedef struct s_redirection
{
	int						fd;
	t_redir_type			type;
	char					*file;
	struct s_redirection	*next_redir;
}	t_redirection;

typedef struct s_process
{
	pid_t				pid;
	char				**command_arguments;
	t_redirection		*redirections; 
	t_environment		*env_vars;
	int					input_fd;
    int					output_fd;
	int					exit_status; //keep it for now but do not need to populate
	bool				is_builtin;
	bool				is_pipeline;//keep it for now but do not need to populate
	t_builtin			*builtin;
	int					completed;
	struct s_process	*next_process;
} t_process;

typedef struct s_minishell
{
	char			*input_str;
	int				input_status;
	char			**heredoc_archive; //handle after lexer
	int				heredoc_count; //helps to cleanup and keep track of the amount of heredoc
	const char		**system_commands;
	const char		**buildin_commands;
	t_token			*token_list;
	t_process		*process_list;
	int				**pipes;
	// t_exit_status	exit_status;		
	int				num_processes;
	t_environment	*env_list;
}	t_minishell;


t_environment	*ft_new_var_lst(char *variable, char *value);
void			ft_var_lstadd_back(t_environment **lst, t_environment *new);

int   			create_env_lst(t_environment **env_list, char **envp);
t_environment	*copy_env_list(t_minishell *shell, t_process *process);

/*init*/
void			init_shell(t_minishell *shell);
t_process		*new_process_lst(t_minishell *shell, char **commands);
t_token			*new_token_lst(char *token);

/*executor - processes/pipes*/
int				create_pipes(t_minishell *shell);
int				assign_fd(t_minishell *shell);
int				create_processes(t_minishell *shell);
int				read_input(int argc, t_minishell *shell);

/*executor*/
void    execute_builtin(t_process *process, t_minishell *shell);

/*executor - redirections*/
int 			redirections(t_process *process_lst);
int 			handle_redirection(t_process *process);

/*executor - execve*/
char			**get_pathdirs(t_process *process);
char    		*get_path(t_process *process);
char    		**execve_get_envvars(t_process *process);

/*cleanup*/
void			ft_lstclear_token(t_token **token_list);
void			ft_lstclear_env(t_environment **env_list);
void			ft_lstclear_redir(t_redirection **redir_list);
void			ft_lstclear_process_envvars(t_process **process);
void			ft_lstclear_process(t_process **process_list);
void			ft_exit(t_minishell *shell, char *error_msg);
void			free_pipes(t_minishell *shell);

/*utils_malloc*/
char			**allocate_array(char **commands);
int				**allocate_pipes(int p_num);

/*utils_processes*/
void			process_lst_add_back(t_process *new_process, t_process **process_lst);
void    		waitpid_children(t_minishell *shell);

/*utils_pipes*/
void			close_pipe_ends(t_minishell *shell, t_process	*current);
void			close_pipe_ends_parent(t_minishell *shell);

/*utils_redir*/
t_redirection    *new_redir_lst(int fd, t_redir_type type, char *file);
void    		redir_lst_add_back(t_redirection *new_redir, t_redirection **redir_lst);

/*utils_builtins*/
void			prt_env_lst(t_environment *env_list);
int    			parse_builtin(t_minishell *shell);

/*signals*/
int				setup_signals();

/*testing*/
void			print_fds(t_minishell *shell);
void    		printf_twod(char **arr);
void			prt_tokenlst(t_minishell *shell);

/*parsing*/
void			tokenize_input(t_minishell *shell);
int				redir_checker(char *command);
int				token_checker(char *command);
void			free_tokenlst(t_minishell *shell);
void			def_token(t_minishell *shell, int t_len, int t_start);
void			def_special_token(t_minishell *shell, int *i);

/*errors*/
void    display_shell_error(char *msg, int exit_status);


#endif


/// stdout = fd1
// ls | cat | grep
/// readin cat = fd7
//  dup so that stdout = fd7
// exec ls -> ls output fd7 


// fork
// child -> stdout = fd7
// parent -> stdout = fd7