#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//验证线程函数传参
//传参方法  1
void *thread_1(void *arg)
{
    int rec = 0;

    sleep(1);
    rec = (int)(arg);
    printf("new thread1 arg = %d\n", rec);
    return NULL;
}

//传参方法  2
void *thread_2(void *arg)
{
    int rec = 0;
    
    sleep(1);
    rec = *((int *)arg);
    printf("new thread2 arg = %d\n", rec);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;
    int test = 100;

    pthread_create(&tid1, NULL, thread_1, (void *)test);
    pthread_create(&tid2, NULL, thread_2, (void *)(&test));
    
    while(1);    
    return 0;
}
