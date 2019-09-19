#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//验证多线程实现多任务，及线程间共享全局变量
int var = 8;

void *thread_1(void *arg)
{
    while(1){
        printf("this is my new thread var++\n");
        var++;
        sleep(1);
    }
    return NULL;
}

void *thread_2(void *arg)
{
    while(1){
        printf("this is my new thread2 var = %d\n", var);
        sleep(1);
    }
    return NULL;

}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;
    
    pthread_create(&tid1, NULL, thread_1, NULL);
    pthread_create(&tid2, NULL, thread_2, NULL);
    
    while(1);    
    return 0;
}
