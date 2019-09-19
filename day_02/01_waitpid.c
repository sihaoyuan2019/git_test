#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    pid_t pid = 0;
    int i = 0;
    for(i=0; i<3; i++)
    {
        pid = fork();
        if(pid == -1)
        {
            perror("fork");
        }
        else if (pid ==0)
        {
            break;
        }

    }

    if(i == 0)
    {
        sleep(1);
        printf("第%d个子进程：%d\n", i+1, getpid());
        _exit(4);
    }
    else if (i == 1)
    {
        sleep(2);
        printf("第%d个子进程：%d\n", i+1, getpid());
        _exit(5);
    }
    else if (i == 2)
    {
        sleep(3);
        printf("第%d个子进程：%d\n", i+1, getpid());
        _exit(6);
    }
    else
    {

        int status;

        while(1)
        {
            //注意第三个参数 为WNOHANG 和 为0 的区别
            pid_t pid = waitpid(-1, NULL, 0);//&status
            if(pid > 0)
            {
                printf("子进程%d退出了\n", pid);
                //if(WIFEXITED(status)!=0)
                //{
                    //printf("子进程%d退出的状态值为：%d\n", pid, WEXITSTATUS(status));
                //}
            
            }
            //else if (pid == 0)
            //{
                //continue;
            //}
            else if (pid == -1)
            {
                break;
            }
        }


    }
    


    return 0;
}
