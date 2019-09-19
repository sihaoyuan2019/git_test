#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void *thread_cancel(void *arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    printf("延时三秒\n");
    while(1)
    {
        //pthread_testcancel();
        //sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid1;
    int ret = 0;

    pthread_create(&tid1, NULL, thread_cancel, NULL);
    if(ret != 0)
        perror("pthread_create");

    sleep(3);
    pthread_cancel(tid1);
    pthread_join(tid1, NULL);
    return 0;
}