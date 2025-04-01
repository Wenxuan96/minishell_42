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
#include "libft.h"

typedef struct minishell
{
	t_token			*token_list;
	t_process		*process_list;
	t_environment	*env_list;
};

/*
Lexer: takes in an input line
output: array of tokens
*/
typedef	enum	e_token_type
{
	WORD,
	REDIRECTION,
	PIPELINE,
}	t_token_type;

typedef struct s_token
{
    int				len;
	char			*start;
	t_token_type	*type;
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

typedef struct s_process
{
	char				**command_arguments;
	t_redirection		*redirections;
	struct s_process	*next_process;
} t_process;

typedef	enum	e_redir_type
{
	OUTPUT, // >
	INPUT, // <
	HEREDOC, // <<
	OUTPUT_APPEND, // >>
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type			*type;
	char					*file;
	struct s_redirection	*next_redir;
}	t_redirection;


typedef struct	s_environment
{
	char					*env_var;
	char					*value;
	struct	s_environment	*next_env_var;
}	t_environment;

t_environment	*ft_new_var_lst(char *variable, char *value);
void			ft_var_lstadd_back(t_environment **lst, t_environment *new);

#endif