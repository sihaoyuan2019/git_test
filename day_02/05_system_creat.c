#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void test(char *p)
{
   
    pid_t pid = 0;
    pid = vfork();
    if(pid == -1)
    {
        perror("fork");
        
    }    
    else if (pid == 0)
    {

        printf("子进程中\n");
        execl("/bin/bash",  "bash","-c", p, NULL);
        //execlp("bash",  "bash","-c", p, NULL);

        //execl一旦执行成功后面的代码 不会继续执行 
        exit(127); 
        printf("----end--execl----\n"); 
    }
    else
    {
        printf("父进程中\n");

        int status = 0;
        pid_t pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("子进程%d退出的状态值为：%d\n", pid, WEXITSTATUS(status));
        }
        
    }
    
}

int main(int argc, char const *argv[])
{
    char str[32]="";

    printf("请输入提示符：\n");
    gets(str);
    printf("%s\n", str);

    test(str);
    return 0;
}

