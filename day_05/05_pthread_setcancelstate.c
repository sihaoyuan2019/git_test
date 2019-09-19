#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//验证设置线程能\ \ 否被取消，然后看线程能不能被取消
void *thread_cancel(void *arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    printf("延时三秒\n");
    while(1)
    {
        printf("this is my new thread_cancel\n");
        sleep(1);
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
    pthread_cancel(tid1);//发送信号使目标线程退出
    pthread_join(tid1, NULL);
    return 0;
}