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

/*
Lexer: takes in an input line
output: array of tokens
*/
typedef struct s_token
{
    int	len;
	char	*start;
	char	type; //(or int type)
	struct s_token	*next_token;
}	t_token; //array of tokens when we read the input line;


/*
Parser: takes in an array of tokens
output: linked list of structs
1. group tokens by pipes into linked list
2. expansions ($HOME etc)
3. go through linked list and look for words -> they become arguments to execute
	also checking the syntaxis
*/

typedef struct s_command
{
	char	*cmd_arguments;
} t_command;

typedef struct	s_environment
{
	char	*env_var;
	char	*value;
	struct	s_environment	*next_env_var;
}	t_environment;



#endif