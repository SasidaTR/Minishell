
#include "../../include/minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0);
    rl_redisplay();
}

void initialize_signals(int sig)
{
    (void)sig;
    signal(SIGINT, &handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
