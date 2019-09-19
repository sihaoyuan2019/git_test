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
    key_t key = ftok("/", 2019);
    printf("key = %#x\n", key);

    int msgId = msgget(key, IPC_CREAT|0666);
    if(msgId < 0)
    {
        perror("msgget");
        return 0;
    }
    printf("msgID = %d\n", msgId);

    MSG msg;
    msg.mtype = 7;
    strcpy(msg.mtext, "hello msg from 7");
    //while(1)
    //{
    msgsnd(msgId, &msg, sizeof(msg.mtext), 0);
    sleep(1);
    //}
    return 0;
}
