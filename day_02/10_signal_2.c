#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#if 0
typedef void (*sighandler_t)(int);

void fun1(int signo)
{
    printf("in fun1\n");
}

void fun2(int signo)
{
    printf("in fun2\n");
}

int main(int argc, char *argv[])
{
    sighandler_t previous = NULL;
    
    previous = signal(SIGINT,fun1);
    if(previous == NULL)
    {
        printf("return fun addr is NULL\n");
    }
    
    previous = signal(SIGINT,fun2);
    if(previous == fun1)
    {
        printf("return fun addr is fun1\n");
    }
    
    previous = signal(SIGQUIT,fun1);
    if(previous == NULL)
    {
        printf("return fun addr is NULL\n");
    }
    
    return 0;
}
#else

static int *p = NULL;

void myDealFun2(int signal)  
{  
    if(p != NULL)  
    {  
        free(p);  
        p = NULL;  
    }  
  
    printf("堆区空间已释放\n");  
  
    _exit(-1);  
}  

int main()  
{  
    
  
    p = (int *)calloc(1,sizeof(int));  
    *p = 100;  
    printf("*p = %d\n", *p);  
    
    //注册CTRL+c的信号  
    signal(SIGINT, myDealFun2);  
    //p = (int *)malloc(sizeof(int)*1);  
    //memset(p,0,sizeof(int));  
#if 1 
    while(1);  
  
    if(p != NULL)  
    {  
        free(p);  
        p = NULL;  
    }  
    printf("函数已结束\n");  
#endif
    return 0;
}  

#endif