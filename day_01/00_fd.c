#include <stdio.h>
#include <string.h>
#include <unistd.h>

void test01()
{
    char buf[32]="";
    read(0, buf, sizeof(buf));

    write(1, buf, strlen(buf));

    return;
}

int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
