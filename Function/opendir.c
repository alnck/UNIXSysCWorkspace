#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH      4096

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *dent;
    struct stat finfo;
    char path[MAX_PATH];

    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((dir = opendir(argv[1])) == NULL)
        exit_sys("open");
    
    while (errno = 0, (dent = readdir(dir)) != NULL) {
        sprintf(path, "%s/%s", argv[1], dent->d_name);
        if (stat(path, &finfo) == -1)
            exit_sys("stat");
        
        printf("-------------------------------\n");
        printf("%-25s%s\n", dent->d_name, S_ISDIR(finfo.st_mode) ? "<DIR>" : "");
        printf("%lld\n", (long long)finfo.st_size);
    }
        
    if (errno != 0)
        exit_sys("readdir");

    closedir(dir);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);  

    exit(EXIT_FAILURE);
}