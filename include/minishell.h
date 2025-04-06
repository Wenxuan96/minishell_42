#ifndef MINISHELL_H
# define MINISHELL_H

#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft.h"

/*
Lexer: takes in an input line
output: array of tokens
*/
typedef	enum	e_token_type
{
	WORD,
	REDIRECTION,
	PIPELINE,
}	t_token_type; // check where & goes - background flag?

typedef	enum	e_redir_type
{
	OUTPUT, // >
	INPUT, // <
	HEREDOC, // <<
	OUTPUT_APPEND, // >>
}	t_redir_type;

typedef	enum e_exit_status
{
	MS_EXIT_FAILURE = 1,
	MS_EXIT_SUCCESS = 0,
	MS_COMMAND_NOT_FOUND = 127,
}	t_exit_status;

typedef struct s_token
{
    int				len;
	char			*start;
	t_token_type	type;
	bool			in_quotes;  // Indicates if the token was enclosed in quotes (if not in_quotes, give an error)
	bool            is_dynamic; //checks if token uses substr to malloc or if it just points to within input_str in shell struct
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
	bool					is_dynamic; //checks if token uses substr to malloc or if it just points to within input_str in shell struct
	struct s_redirection	*next_redir;
}	t_redirection;

typedef struct s_process
{
	char				**command_arguments;
	t_redirection		*redirections;
	int					input_fd;  // File descriptor for input redirection
    int					output_fd; // File descriptor for output redirection
	struct s_process	*next_process;
	pid_t				pid;
} t_process;

typedef struct	s_environment
{
	char					*env_var;
	char					*value;
	struct	s_environment	*next_env_var;
}	t_environment;

typedef struct s_minishell
{
	char			*input_str;
	t_token			*token_list;
	t_process		*process_list;
	int				num_processes;
	t_environment	*env_list;
}	t_minishell;

t_environment	*ft_new_var_lst(char *variable, char *value);
void			ft_var_lstadd_back(t_environment **lst, t_environment *new);

int   create_env_lst(t_environment **env_list, char **envp);


//test
int			create_pipes(t_minishell *shell);
t_process	*new_process_lst(char **commands);
int			create_processes(t_minishell *shell);
int	read_input(int argc, char **argv, t_minishell *shell);
//cleanup
void	ft_lstclear_token(t_token **token_list);
void	ft_lstclear_env(t_environment **env_list);
void	ft_lstclear_redir(t_redirection **redir_list);
void	ft_lstclear_process(t_process **process_list);
void	ft_exit(t_minishell *shell, char *error_msg);
#endif