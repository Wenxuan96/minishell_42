/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:27 by tignatov          #+#    #+#             */
/*   Updated: 2025/04/24 16:53:50 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0;

void    sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    g_exit_status = 128 + SIGINT;
    //reprint the prompt?
}

int setup_signals()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
    signal(SIGQUIT, SIG_IGN);
    return (1);
}
