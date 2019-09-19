#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void test03()
{
    int fd = 0;
    fd = open("./a.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return;
    }
    printf("fd = %d\n",fd);

    char buf[128] = "";
    int len = read(fd, buf, sizeof(buf));
    printf("len = %d\n", len);
    printf("buf = %s\n", buf);

    close(fd);
    remove("./a.txt");//删除指定路径的文件
    
    return;
}

int main(int argc, char const *argv[])
{
    test03();
    return 0;
}
