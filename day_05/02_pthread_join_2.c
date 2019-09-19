#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//验证 pthread_join 接收线程的返回值
void *thead(void *arg)
{
    int num = 123;

    printf("after 2 seconds, thread will return\n");
    sleep(2);
    return (void *)num;
}

int main(int argc, char *argv[])
{
    pthread_t tid1;
    int ret = 0;
    int value = 0;

    ret = pthread_create(&tid1, NULL, thead, NULL);
    if(ret != 0)
        perror("pthread_create");

    pthread_join(tid1, (void *)(&value));
    printf("value = %d\n", value);

    return 0;
}
