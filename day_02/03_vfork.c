#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid = 0;
    
    int num = 0;
    int i = 0;
    pid = vfork();
    if(pid == -1)
    {
        perror("vfork");
        return 0;
    }
    else if(pid == 0)
    {
        sleep(1);
        printf("I am a child:%d, my father is %d\n", getpid(), getppid());
        
        for( i = 0; i < 3; i++)
        {
            num++;
            printf("num = %d\n",num);
        }
        
        
        _exit(3);
    }
    else
    {
        //sleep(2);
        printf("I am father:%d\n", getpid());
        
        
        printf("num = %d\n",num);
        pid_t pid = wait(NULL);
        if(pid == -1 )
        {
            perror("wait");
            return 0;
        }
        else
        {
            printf("子进程%d退出\n", pid);
        }
        

    }
    
    return 0;
}
