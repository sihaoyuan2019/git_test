#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <semaphore.h> 

sem_t sem;  

void myPrintf(void *arg)  
{  
    char *str = (char *)arg;  
    while(*str)   //!= '\0'
    {  
        printf("%c", *str++);  
        fflush(stdout);  
        sleep(1);  
    } 
    puts("");
}  

void *thread_fun1(void *arg)  
{  
    //P操作 -1  
    sem_wait(&sem);  
    myPrintf(arg);  
    sem_post(&sem);  
    //V操作 +1  
}  

void *thread_fun2(void *arg)  
{  
    //P操作 -1  
    sem_wait(&sem);  
    myPrintf(arg);  
    sem_post(&sem);  
    //V操作 +1  
}  

int main(int argc, char *argv[])  
{  
    pthread_t tid1;  
    pthread_t tid2;  
    
    //信号量的创建以及初始化  
    sem_init(&sem, 0, 1);  

    
    pthread_create(&tid1, NULL, thread_fun1, "hello"); 
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun2, "world");  
     
    pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);     
    
      
    //信号量的销毁  
    sem_destroy(&sem);  
    return 0;  
}  