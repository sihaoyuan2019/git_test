#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <semaphore.h>  
#include <sys/wait.h>  
#include <semaphore.h>  
//#include <sys/types.h>  
//#include<sys/stat.h>  
#include <fcntl.h>  

void myPrintf(void *arg)  
{  
    char *str = (char *)arg;  
    while(*str != '\0')  
    {  
        printf("%c",*str++);  
        fflush(stdout);  
        usleep(1000*1000);  
    }  
}  

int main(int argc, char const *argv[])  
{  
    pid_t pid;  
    int i=0;  
    for(i =0; i<2; i++)  
    {  
        pid = fork();  
        if(pid<0)  
        {  
            perror("fork");  
            return 0;  
        }  
        else if(pid == 0)  
        {  
            break;  
        }  
    }  
  
    if(i == 0)//子进程1  
    {  
       
        sem_t *sp1 = sem_open("mutex",O_CREAT|O_RDWR, 0666, 1);  
        printf("????\n");
        //p操作 -1  
        sem_wait(sp1);  
        myPrintf("hello ");  
        //v操作 +1  
        sem_post(sp1);  
  
        //回收sp1的空间  
        sem_close(sp1);  
    }  
    else if(i == 1)//子进程2  
    {  
        sem_t *sp1 = sem_open("mutex",O_CREAT|O_RDWR, 0666, 1);  
        printf("!!!!\n");
        //p操作 -1  
        sem_wait(sp1);  
        myPrintf("world");  
        //v操作 +1  
        sem_post(sp1);  
  
        //回收sp1的空间  
        sem_close(sp1);  
    }  
    else if(i == 2)//父进程  
    {  
        while(1)  
        {  
            pid = waitpid(-1, NULL, WNOHANG);  
            if(pid >0 )//子进程号为pid的进程退出了  
            {  
                // printf("子进程%d退出了\n", pid);  
            }  
            else if(pid == 0)//还有子进程未退出  
            {  
                continue;  
            }  
            else if(pid < 0)  
            {  
                break;  
            }  
        }  
  
        printf("\n");  
        //删除有名信号量  
        sem_unlink("mutex");  
         
    }  
    return 0;  
}  