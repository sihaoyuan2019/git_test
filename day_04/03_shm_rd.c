#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>


int main(int argc, char *argv[])
{
    //创建一个唯一的键值
    key_t key = ftok("/", 2019);
    //根据key创建一个物理共享内存标识符
    int shmId = shmget(key, 128, IPC_CREAT|0600);//当前用户的权限
    //根据物理内存标识符映射虚拟内存  NULL自动分配  0可读可写
    char *addr = NULL;
    addr = shmat(shmId, NULL, 0);
    if(addr == NULL)
    {
        perror("shmat");
        return 0;
    }

    //借助addr虚拟地址
    //strcpy(addr, "hello share memory");

    
    while(1)
    {
        printf("addr = %p------%s\n", addr , addr);  
    }
    return 0;
}
