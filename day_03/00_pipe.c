#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void test01()
{
    int fd[2] = {0};
    //创建无名管道，
    if(pipe(fd) < 0)
    {
        perror("pipe");
    }

    //fd[0]用于读数据，fd[1]用于往管道写数据
    printf("fd[0] = %d\n", fd[0]);
    printf("fd[1] = %d\n", fd[1]);


    //创建子进程
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        //printf("fd[0] = %d\n", fd[0]);
        //printf("fd[1] = %d\n", fd[1]);
        //写入数据

        close(fd[0]);
        sleep(2);
        write(fd[1],"hello pipe", strlen("hello pipe"));
        sleep(2);
        exit(-1);
        close(fd[1]);
    }
    else
    {
        
        close(fd[1]);

        fcntl(fd[0], F_SETFL, O_NONBLOCK);
        while(1)
        {
            char buf[128]="";
            int len = read(fd[0], buf,sizeof(buf));
            printf("len = %d\n", len);
            printf("buf = %s\n", buf);
            //wait(NULL);
            if (len != -1) {
                break;
            }
        }     
    
       
        close(fd[0]);
    }
    
    while(1);
    return;

}

int main(int argc, char const *argv[])
{
    test01();

    return 0;
}
