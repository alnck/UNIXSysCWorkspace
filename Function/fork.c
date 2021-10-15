#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys (const char *msg);

int g_a;

int main(void)
{
    pid_t pid;
    int i;

    for (i = 0; i < 3; ++i)
        if ((pid = fork()) == -1)
            exit("fork");
    
    printf("running...\n");
    
    getchar();
    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}