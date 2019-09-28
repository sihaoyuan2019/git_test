#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

void test02()
{
    int fd = 0;
    fd = open("./test.txt", O_WRONLY|O_CREAT|O_EXCL, 0700);    
    //  O_EXCL如果同时指定了O_CREAT，文件已经存在则出错，即必保证原文件不存在
    if(fd == -1)
    {
        perror("open");
        return;
    }
    printf("fd = %d\n",fd);

    char str[] = "hellofile";

    int a = sizeof(str);    // 10
    int b = strlen(str);    // 9
    printf("a = %d\n", a);  
    printf("b = %d\n", b);  

    //write(fd, str, sizeof(str));
    //write(fd, str, strlen(str));

    close(fd);

    return;
}

int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
