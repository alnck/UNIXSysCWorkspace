#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>


void walkdir(const char *path)
{
    DIR *dir;
    struct dirent *ent;
    struct stat finfo;

    if (chdir(path) == -1)
        return;

    if ((dir = opendir(path)) == NULL)
        return;

    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;
        
        if ((lstat(ent->d_name, &finfo)) == -1)
            continue;

        if (S_ISDIR(finfo.st_mode)) {
            walkdir(ent->d_name);
            if (chdir("..") == -1)
                break;
        }
    }
}

int main(void)
{
    walkdir(".");

    return 0;
}