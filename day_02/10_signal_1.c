#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo)
{
    if(signo==SIGINT)
    printf("recv SIGINT\n");
    if(signo==SIGQUIT)
    printf("recv SIGQUIT\n");
}

int main(int argc, char *argv[])
{
    printf("wait for SIGINT OR SIGQUIT\n");
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    pause();
    pause();
    return 0;
}