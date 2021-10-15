#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
  pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
        exit_sys("fork");

    if (pid == 0 && execv(argv[1], &argv[1]) == -1)
        exit_sys("execv");

    if (wait(NULL) == -1)
        exit_sys("wait");
        
  return 0;
}

void exit_sys(const char *msg)
{
  perror(msg);

  exit(EXIT_FAILURE);
}