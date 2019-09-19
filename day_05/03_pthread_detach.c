#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thead(void *arg)
{
    int i;
    for( i = 0; i < 5; i++)
    {
        printf("I am running\n");
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    pthread_t tid1;

    ret = pthread_create(&tid1, NULL, thead, NULL);
    if(ret != 0)
    {
        perror("pthread_create");
    }

    pthread_detach(tid1);
    pthread_join(tid1, NULL);
    printf("after join\n");
    sleep(6);
    printf("I am leaving\n");

    return 0;
}
