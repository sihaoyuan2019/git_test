#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("请按：./main src dst 传参\n");
        return 0;
    }

    //打开源文件
    int srcFd = 0;
    srcFd = open(argv[1], O_RDONLY);
    if (-1 == srcFd) {
        perror("open");
        return 0;
    }

    //打开目标文件
    int dstFd = 0;
    dstFd = open(argv[2], O_WRONLY|O_CREAT, 0777);
    if (-1 == dstFd) {
        perror("open");
        return 0;
    }

    while(1)
    {
        char buf[128] = "";
        int len = read(srcFd, buf, sizeof(buf));
        if (len <= 0) {
            break;
        }
        write(dstFd, buf, len);
    }

    close(srcFd);
    close(dstFd);
    



    return 0;
}
