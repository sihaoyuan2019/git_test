#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int seconds = 0;
    seconds = alarm(5);
    printf("seconds = %d\n", seconds);
    sleep(2);
    seconds = alarm(5);
    printf("seconds = %d\n", seconds);
    while(1);
    return 0;
}