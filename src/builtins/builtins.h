#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"

typedef int builtin_func(t_minishell *shell);

typedef struct s_builtin
{
    t_builtin_type   type;
    builtin_func    *function;
}   t_builtin;

int cd_builtin(t_minishell *shell);
int pwd_builtin(t_minishell *shell);
int export_builtin(t_minishell *shell);
int env_builtin(t_minishell *shell);
int exit_builtin(t_minishell *shell);
int unset_builtin(t_minishell *shell);
int echo_builtin(t_minishell *shell);


t_builtin   *new_builtin(t_builtin_type type, builtin_func *function);
void    assign_builtin(t_process *process);


#endif