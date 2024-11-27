/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:20:18 by earnera           #+#    #+#             */
/*   Updated: 2024/11/27 17:47:05 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    //printf("\nminishell> ")
    //redisplay
    //fflush
}

void initialize_signals(int sig)
{
    (void)sig;
    signal(SIGINT, &handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
