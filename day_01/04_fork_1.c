#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
#if 0
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgid(0);//0表示获取当前进程的进程组号


    printf("pid = %d\n", pid);
    printf("ppid = %d\n", ppid);
    printf("pgid = %d\n", pgid);

#else
    int num = 10;
    pid_t pid = fork();
    if (pid == -1) {
        perror("创建失败");
    }else if(pid == 0){
        while(1)
        {
            num++;
            printf("子进程中：num = %d\n",num);
            pid_t pid = getpid();
            printf("pid = %d\n", pid);

            sleep(1);
        }
    }else{
        while(1)
        {
            printf("父进程中：num = %d\n",num);
            pid_t ppid = getppid();
            printf("ppid = %d\n", ppid);
            sleep(1);
        }
    }
#endif
    return 0;
}
