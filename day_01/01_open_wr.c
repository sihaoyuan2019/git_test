#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void test02()
{
    int fd = 0;
    fd = open("./a.txt", O_WRONLY|O_CREAT|O_EXCL, 0700);
    if(fd == -1)
    {
        perror("open");
        return;
    }
    printf("fd = %d\n",fd);

    char str[] = "hello file！";
    write(fd, str, sizeof(str));

    close(fd);


    return;
}

int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
