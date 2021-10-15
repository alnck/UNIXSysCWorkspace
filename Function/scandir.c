#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int mycallback(const struct dirent *de)
{
	struct stat finfo;
    char path[4096];

    sprintf(path, "/usr/include/%s", de->d_name);

    if(stat(path, &finfo) == -1){
        exit_sys("stat");
            }
    /*if (tolower(de->d_name[0]) == 'a')
		return 1;*/

	return finfo.st_size < 1000;
}

int cmp(const struct dirent **de1, const struct dirent **de2)
{
    return strcmp((*de1)->d_name, (*de2)->d_name);
}

int main(void)
{
	struct dirent **dents;
	int i, count;

	if ((count = scandir("/usr/include", &dents, mycallback, NULL)) == -1) // 4. parametre karşılaştırma fonksiyonu
		exit_sys("scandir");

	for (i = 0; i < count; ++i)
		printf("%s\n", dents[i]->d_name);

	for (i = 0; i < count; ++i)
		free(dents[i]);

	free(dents);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}