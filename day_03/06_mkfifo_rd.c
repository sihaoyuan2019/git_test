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
    int ret = mkfifo("my_fifo", 0777);
    if(ret = -1)
    {
        perror("mkfifo");

    }

    //使用open打开my_fifo 目的获得文件描述符（对命名管道读写操作）
    int fd = open("my_fifo", O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return;
    }

    while(1)
    {
        char buf[128]="";
        int len = read(fd, buf, sizeof(buf));
        printf("len = %d\n", len);
        printf("bur = %s\n", buf);
        sleep(1);
        
    }

    close(fd);


}

int main(int argc, char *argv[])
{
    
    //test01();
       
    sleep(1); 
    printf("argv[1] = %s\n", argv[1]);


    return 0;
}
