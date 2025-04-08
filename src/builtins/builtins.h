#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"

typedef int builtin_func(t_minishell *shell);

typedef struct s_buildin
{
    char            *name;
    builtin_func    *function;
}   t_builtin;

int cd_builtin(t_minishell *shell);
int pwd_builtin(t_minishell *shell);
int export_builtin(t_minishell *shell);
int env_builtin(t_minishell *shell);
int exit_builtin(t_minishell *shell);
int unset_builtin(t_minishell *shell);
int echo_builtin(t_minishell *shell);




#endif