#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //创建管道
    int fd[2] = {0};
    pipe(fd);

    
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
    }
    else if(pid == 0)//子进程
    {
        close(fd[1]);

        //将 0 复制到fd[0]上
        dup2(fd[0], 0);
        
        execlp("grep", "grep", "bash", NULL);
        //system("grep bash");  //system存在小问题，不会正常退出，所以用exec
        close(fd[0]);
        exit(-1);




    }
    else//父进程
    {
        //关闭读端
        close(fd[0]);

        //将 1  复制到fd[1]
        dup2(fd[1], 1);
        execlp("ps", "ps", "-aux", NULL);
        
        //system("ps -aux");
        wait(NULL);
        close(fd[1]);

    }
    



    return 0;
}
