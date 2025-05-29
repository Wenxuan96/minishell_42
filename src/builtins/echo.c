/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:08:01 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/29 16:32:37 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"


// char *p1_cmd[] = {"echo", "this is a test", NULL};
// char *p2_cmd[] = {"grep", "test", NULL};
// char *p3_cmd[] = {"wc", "-w", NULL};

// echo "this is a test" | grep test | wc -w


int	echo_builtin(t_process *process, t_minishell *shell)
{
    int i;
    int no_newline;

    i = 1;
    no_newline = 0;
    (void)shell;
    while (process->command_arguments[i] && ft_strlen(process->command_arguments[i]) > 1 && process->command_arguments[i][0] == '-')
    {
        int j = 1;
        while (process->command_arguments[i][j] == 'n')
            j++;
        if (process->command_arguments[i][j] != '\0')
            break;
        no_newline = 1;
        i++;
    }
    while (process->command_arguments[i])
    {
        write(STDOUT_FILENO, process->command_arguments[i], ft_strlen(process->command_arguments[i]));
        if (process->command_arguments[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!no_newline)
        write(STDOUT_FILENO, "\n", 1);
    return (1);
}
