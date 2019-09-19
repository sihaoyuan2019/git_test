#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//静态分配的互斥锁
//pthread_mutex_t mutex;

void *thread_fun(void *arg)
{
    char *str = (char *)arg;
    //上锁
    pthread_mutex_lock(&mutex);
    //pthread_mutex_trylock(&mutex);
    int i = 0;
    while(str[i] != '\0')
    {
        printf("%c", str[i++]);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    //解锁
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{   
    pthread_t tid1;
    pthread_t tid2;

    //pthread_mutex_init(&mutex, NULL);//动态申请锁
    pthread_create(&tid1, NULL, thread_fun, "hello");
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun, "world");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    //销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}


