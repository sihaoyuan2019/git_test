#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid = 0;
    int i = 0;
    for(i=0;i<2;i++)
    {
        pid = fork();
        if(pid == -1)
        {
            perror("fork");
            return 0;
        }
        else if(pid == 0)
        {
            break;
        }
    }
    if(i == 0)
    {
        sleep(2);
        
        printf("I am a child:%d, my father is %d\n", getpid(), getppid());
        _exit(3);
    }
    else if(i == 1)
    {
        sleep(2);
        printf("I am a child:%d, my father is %d\n", getpid(), getppid());
        _exit(4);
    }
    else
    {
        //sleep(2);
        printf("I am father:%d\n", getpid());
        while(1)
        {
        int status = 0;
        pid_t pid = wait(&status);
        if(pid == -1 )
        {
            break;
        }
        if(WIFEXITED(status)!=0)
        {
            printf("子进程%d退出的状态值为：%d\n", pid, WEXITSTATUS(status));
        }
        

        }

    }
    
    return 0;
}
