#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//验证pthread_join的阻塞效果
void *thread(void *arg)
{
    static int num = 123;

    printf("after 2 seconds, thread will return\n");
    sleep(2);
    return &num;
}

int main(int argc, char const *argv[])
{
    pthread_t tid1;
    int ret = 0;
    void *value = NULL;

    ret = pthread_create(&tid1, NULL, thread, NULL);
    if(ret != 0)
    {
        perror("pthread_create");
    }

    pthread_join(tid1, &value);
    printf("value = %d\n", *(int *)value);

    return 0;
}
