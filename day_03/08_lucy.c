#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    pid_t pid = 0;
    int i = 0;
    for(i = 0; i < 2; i++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork");
            return 0;
        }
        else if (pid == 0)
        {
            break;
        }

    }
    
    if (i == 0)//向lucy_to_bob写数据
    {
        //创建一个lucy_to_bob的命名管道
        mkfifo("lucy_to_bob", 0777);
        //以只写的方式打开
        int fd = open("lucy_to_bob", O_WRONLY);
        if (fd < 0) 
        {
            perror("open");
            exit(-1);
        }
        //不停的给bob发消息，遇到quit退出
        while(1){
            printf("Send:");
            char buf[128]="";
            fgets(buf, sizeof(buf), stdin);
            buf[strlen(buf)-1] = 0;//去掉回车

            if (strncmp(buf, "quit", 4) == 0) {
                break;
            }
            //写数据
            write(fd, buf, strlen(buf));
            
        }
    
        close(fd);
        exit(-1);
    }
    else if (i == 1)//从bob_to_lucy读数据
    {
        //创建bob_to_lucy的命名管道
        mkfifo("bob_to_lucy", 0777);
        //以只读方式打开
        int fd = open("bob_to_lucy", O_RDONLY);
        if(fd < 0)
        {
            perror("open");
            exit(-1);
        }
        //不停的接收数据
        while(1){
            char buf[128]="";
            int len = read(fd, buf, sizeof(buf));
            if(len == 0)
            {
                break;
            }
            printf("\rRecv From Bob:%s\n",buf);
            printf("Send:");
            fflush(stdout);

        }
        close(fd);
        exit(-2);


    }
    else
    {
        while(1)
        {
            pid_t pid = waitpid(-1, NULL, WNOHANG);
            if(pid > 0)
            {
                printf("子进程%d退出了\n",pid);
            }
            else if (pid == 0)//还有子进程没有退出，继续等待
            {
                continue;
            }
            else if(pid == -1)//所有子进程都退出了
            {
                break;
            }
            
        }
    }
    

    return 0;
}
