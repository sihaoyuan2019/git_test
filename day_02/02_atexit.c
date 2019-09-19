#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clear_fun1(void)
{
    printf("perform clear fun1 \n");
}

void clear_fun2(void)
{
    printf("perform clear fun2 \n");
}

void clear_fun3(void)
{
    printf("perform clear fun3 \n");
}

int main(int argc, char *argv[])
{
    atexit(clear_fun1);
    atexit(clear_fun2);
    atexit(clear_fun3); //栈式存储！！！
    
    printf("process exit 3 sec later!!!\n");
    sleep(3);
    return 0;
}