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
    int fd = 0;
    fd = open("a.txt", O_WRONLY);
    if(fd < 0)
    {
        perror("open");
    }
    printf("fd = %d\n", fd);

    //关闭标准输出文件描述符
    close(1);
    //复制fd文件描述符：新的文件描述符，是文件描述符列表中最小可用的，而上步已经将1关闭
    int fd1 =dup(fd);
    //本来printf默认往1输出数据，而文件描述符1被重定向到a.txt中
    //所以输出的数据到了a.txt中
    printf("fd1 = %d\n", fd1);


    close(fd);


}

void test02()
{
    int fd = 0;
    fd = open("a.txt", O_WRONLY);
    if(fd < 0)
    {
        perror("open");
    }
    printf("fd = %d\n", fd);

    dup2(fd, 1);
    //本来printf默认往1输出数据，而文件描述符1被重定向到a.txt中
    //所以输出的数据到了a.txt中
    printf("xxxxxfd = %d\n", fd);


    close(fd);


}



int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
