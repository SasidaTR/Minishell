
#include "../../include/minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_redisplay();
    //fflush
}

void initialize_signals(int sig)
{
    (void)sig;
    signal(SIGINT, &handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
