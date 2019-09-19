#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdlib.h>

#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>



int var = 10;

int main(int argc, char const *argv[])
{

#if 0
    printf("a");
    pid_t pid = 0;
    int i = 0;
    for( i = 0; i < 2; i++)
    {
        pid = fork();
        if (pid == -1) {
            return 0;
        }else if (pid == 0)
        {
            break;
        }
    }
    
    if(i == 0)
    {	
		while(1){
        printf("A");
		sleep(3);
		}
    }
    else if (i == 1)
    {
		sleep(1);
		while(1){
        printf("B");
        sleep(3);
        }
    }
    else if(i == 2)
    {
		sleep(2);
		while(1){
        printf("C");
        sleep(3);
		}
    }
#endif

#if 0

    pid_t pid;
    int num=9;
    pid=fork();
    if(pid<0){
        perror("fork");
    }

    if(pid==0){
        var++;
        num++;
        printf("in son process var=%d,num=%d\n", var, num);
    }
    else{
        sleep(1);
        printf("in father process var=%d,num=%d\n", var, num);
    }
    
    printf("common code area\n");

#else

    pid_t pid = 0;
    int i = 0;
    for( i = 0; i < 2; i++)
    {
        pid = fork();
        if (pid == -1) {
            return 0;
        }else if (pid == 0)
        {
            break;
        }
    }
    
    if(i == 0)
    {   
        while(1){
        printf("A I am %d child = %d, ppid = %d\n",i, getpid(), getppid());
        sleep(3);
        }
    }
    else if (i == 1)
    {
        sleep(1);
        while(1){
        printf("B I am %d child = %d, ppid = %d\n", i, getpid(), getppid());
        sleep(3);
        }
    }
    else if(i == 2)
    {
        sleep(2);
        while(1){
        printf("C 父进程pid = %d\n", getpid());
        sleep(3);
        }
    }
    //while(1);
#endif

    return 0;
}
