/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:27 by tignatov          #+#    #+#             */
/*   Updated: 2025/05/27 10:49:18 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0;
// typedef void (*t_sig_handler)(int);

void    sig_handler_parent(int sig)
{
    (void)sig;
    // dprintf(2, "weare triggered signal in parent\n");
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_exit_status = 128 + SIGINT;
    // dprintf(2, "exit status: %u\n", g_exit_status);
    //reprint the prompt?
}

int setup_signals(int is_child)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    ft_memset(&sa_int, 0, sizeof(sa_int));
    ft_memset(&sa_quit, 0, sizeof(sa_quit));
    
    sigemptyset(&sa_int.sa_mask);
    sigemptyset(&sa_quit.sa_mask);
    
    if (is_child == 0)
    {
        sa_int.sa_flags = 0;
        sa_int.sa_handler = sig_handler_parent;
        if (sigaction(SIGINT, &sa_int, NULL) == -1)
        {
            perror("sigaction parent");
            return (0);
        }
        sa_quit.sa_flags = 0;
        sa_quit.sa_handler = SIG_IGN;
        if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
        {
            perror("sigaction parent");
            return (0);
        }
    }
    else
    {
        sa_int.sa_handler = SIG_DFL;
        sa_quit.sa_handler = SIG_DFL;
        if (sigaction(SIGINT, &sa_int, NULL) == -1)
            perror("sigaction child");

        if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
            perror("sigaction child");
    }
    return (1);
}
