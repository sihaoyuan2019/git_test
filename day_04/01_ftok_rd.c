#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

typedef struct 
{
    long mtype;
    char mtext[128];
}MSG;


int main(int argc, char const *argv[])
{
    MSG msg;
    key_t key = ftok("/", 2019);
    printf("key = %#x\n", key);

    int msgId = msgget(key, IPC_CREAT|0666);
    if(msgId < 0)
    {
        perror("msgget");
        return 0;
    }
    printf("msgID = %d\n", msgId);

   
    printf("开始接受\n");
    //while(1)
    //{
    msgrcv(msgId, &msg, sizeof(msg.mtext), 0, 0);
    printf("Recv From NO.%ld:%s\n", msg.mtype, msg.mtext);
    //}
    msgctl(msgId, IPC_RMID, NULL);
    return 0;
}
