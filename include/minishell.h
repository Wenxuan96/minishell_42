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

typedef struct s_token
{
    int	len;
	char	*start;
	char	type; //(or int type)
}	t_token; //array of tokens when we read the input line;

#endif