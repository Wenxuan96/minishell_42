/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:56:13 by wxi               #+#    #+#             */
/*   Updated: 2025/04/26 19:56:14 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"

typedef int builtin_func(t_process *process, t_minishell *shell);

typedef enum	e_builtin_type
{
	CD,
	PWD,
	EXPORT,
	ENV,
	EXIT,
	UNSET,
	ECHO,
}	t_builtin_type;

typedef struct s_builtin
{
    t_builtin_type   type;
    builtin_func    *function;
}   t_builtin;

int cd_builtin(t_process *process, t_minishell *shell);
int pwd_builtin(t_process *process, t_minishell *shell);
int export_builtin(t_process *process, t_minishell *shell);
int env_builtin(t_process *process, t_minishell *shell);
int	exit_builtin(t_process *process, t_minishell *shell);
int unset_builtin(t_process *process, t_minishell *shell);
int echo_builtin(t_process *process, t_minishell *shell);


t_builtin	*new_builtin(t_builtin_type type, builtin_func *function);
void		assign_builtin(t_process *process, t_builtin_type type, builtin_func *function);
void		ft_clean_exit(t_minishell *shell);
void		free_pipes(t_minishell *shell);

#endif