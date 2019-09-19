#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <semaphore.h> 

#if 1
sem_t s1,s2,s3;  

void myPrintf(void *arg)  
{  
    char *str = (char *)arg;  
    while(*str != '\0')  
    {  
        printf("%c",*str++);  
        fflush(stdout);  
        usleep(1000*500);  
    }
    printf("\n");
}  

void *thread_fun1(void *arg)  
{  
    //P操作 -1  
    sem_wait(&s1);  
    myPrintf(arg);  
    sem_post(&s2);  
    //V操作 +1  
      
}  

void *thread_fun2(void *arg)  
{  
    //P操作 -1  
    sem_wait(&s2);  
    myPrintf(arg);  
    sem_post(&s3);  
    //V操作 +1  
      
}  

void *thread_fun3(void *arg)  
{  
    //P操作 -1  
    sem_wait(&s3);  
    myPrintf(arg);  
    sem_post(&s1);  
    //V操作 +1  
}  

int main(int argc, char const *argv[])  
{  
    pthread_t tid1;  
    pthread_t tid2;  
    pthread_t tid3;  
  
    //信号量的创建以及初始化  
    sem_init(&s1, 0, 1);  
    sem_init(&s2, 0, 0);  
    sem_init(&s3, 0, 0);  
  
    pthread_create(&tid1, NULL, thread_fun1, "hello");//s1  
    pthread_create(&tid2, NULL, thread_fun2, "world");//s2  
    pthread_create(&tid2, NULL, thread_fun3, "老弟来了");//s3  
  
    pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);  
    pthread_join(tid3, NULL);  
  
    //信号量的销毁  
    sem_destroy(&s1);  
    sem_destroy(&s2);  
    sem_destroy(&s3);  
  
    return 0;  
}

#else

sem_t sem_g,sem_p; //定义两个信号量
char ch = 'a';

void * pthread_g(void *arg) //此线程改变字符 ch 的值
{
    while(1)
    {
        sem_wait(&sem_g);
        ch++;
        sleep(1);
        sem_post(&sem_p);
    }
}

void * pthread_p(void *arg) //此线程打印 ch 的值
{
    while(1)
    {
        sem_wait(&sem_p);
        printf("%c",ch);
        fflush(stdout);
        sem_post(&sem_g);
    }
}

int main(int argc, char *argv[])
{
    pthread_t tid1,tid2;

    sem_init(&sem_g, 0, 0); //初始化信号量
    sem_init(&sem_p, 0, 1);

    pthread_create(&tid1,NULL,pthread_g,NULL);
    pthread_create(&tid2,NULL,pthread_p,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    return 0;
}

#endif