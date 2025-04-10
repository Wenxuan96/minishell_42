#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"

typedef int builtin_func(t_process *process);

typedef struct s_builtin
{
    t_builtin_type   type;
    builtin_func    *function;
}   t_builtin;

int cd_builtin(t_process *process);
int pwd_builtin(t_process *process);
int export_builtin(t_process *process);
int env_builtin(t_process *process);
int exit_builtin(t_process *process);
int unset_builtin(t_process *process);
int echo_builtin(t_process *process);


t_builtin   *new_builtin(t_builtin_type type, builtin_func *function);
void    assign_builtin(t_process *process);


#endif