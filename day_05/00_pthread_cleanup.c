#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *fun1(void *arg)
{
    static int i = 0;
    while(1)
    {
        i++;
        printf("---%s---\n", (char *)arg);
        sleep(1);
        if(i == 5)
            break;

    }
    return &i;

}
void *fun2(void *arg)
{
    static int i = 0;
    while(1)
    {
        i++;
        printf("---%s---\n", (char *)arg);
        sleep(1);
        if(i == 3)
            break;

    }
    return &i;

}
void test02()
{
    pthread_t tid1 = 0;
    pthread_t tid2 = 0;

    pthread_create(&tid1, NULL, fun1, "data1");
    pthread_create(&tid2, NULL, fun2, "data2");

    void *ret = NULL;
    pthread_join(tid1, &ret);
    printf("ret = %d\n", *(int *)ret);

    pthread_join(tid2, &ret);
    printf("ret = %d\n", *(int *)ret);

    return;
}

//线程结束时的清理函数
void cleanCallocMem(void *arg)//arg = str
{
    printf("调用了清理函数\n");
    if(arg != NULL)
    {
        free(arg);
        arg = NULL;
    }
    return;
}
void *fun_d1(void *arg)
{
    
    char *str = NULL;
    str = (char *)calloc(1, 128);
    //注册清理函数
    pthread_cleanup_push(cleanCallocMem, str);

    strcpy(str, "helllo\n");
    printf("str = %s\n", str);

    //sleep(2);
    //pthread_exit(NULL);//也要执行清理函数
    //printf("---end exit---\n");

    //弹出清理函数
    pthread_cleanup_pop(1);//参数1的目的 弹出清理函数并执行
    return NULL;
}
void test06()
{
    //定义线程号
    pthread_t tid = 0;
    //创建线程
    pthread_create(&tid, NULL, fun_d1, NULL);
    //线程分离
    pthread_detach(tid);
    
    getchar();
}

int main(int argc, char *argv[])
{
    test06();
    return 0;
}
