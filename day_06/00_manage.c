#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <semaphore.h>

sem_t sem;
//sem_t sp;  
int num = 5;
void *thread_product(void *arg)  
{  
        
    while(num < 10)
    {
        usleep(1000*500);
        //P操作 -1    
        sem_wait(&sem);
        num++;
        printf("生产中------%d\n",num);  
        
        sem_post(&sem);
        sem_post(&sem);
        //V操作 +1  
        if(num == 10)
            sleep(7);
    }    
}  
  
  
void *thread_sale(void *arg)  
{
    while(num > 0)
    {
        usleep(1000*1000);
        //P操作 -1  
        sem_wait(&sem);  
        num--;
        printf("消费中------%d\n",num);  
        
        //sem_post(&sem);  
        //V操作 +1  
        if(num ==0)
        {
            sem_post(&sem);
            sleep(5);
        }
    }
}  

int main(int argc, char const *argv[])  
{  
    pthread_t tid1;  
    pthread_t tid2;  
    //信号量的创建以及初始化  
    sem_init(&sem, 0, 5);  
    //sem_init(&sem, 0, 0);  

    //sp = ((sem_t)10)-sem;
        
    pthread_create(&tid1, NULL, thread_product, NULL);
       
    pthread_create(&tid2, NULL, thread_sale, NULL);  
          
    pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);     
    

      
    //信号量的销毁  
    sem_destroy(&sem);  
    return 0;  
}  