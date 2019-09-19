#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <semaphore.h>  
#include <sys/wait.h>  
#include <semaphore.h>  
#include <sys/mman.h> 

int main(int argc, char *argv[])
{
    pid_t pid;
    int i = 0;
    for( i = 0; i < 2; i++)
    {
        pid = fork();
        if(pid == -1)
        {
            perror("fork");
        }
        else if(pid == 0)
        {
            break;
        }
    }

    if(i == 0)
    {
        
    }
        



    return 0;
}
