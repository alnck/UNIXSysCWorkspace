#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_proc1(void* param);
void *thread_proc2(void* param);
void exit_errno(const char* msg, int result);

int g_count;

int main(void)
{
	int result;
	pthread_t tid1, tid2;

    if ((result = pthread_create(&tid1, NULL, thread_proc1, NULL)) != 0)
		exit_errno("pthread_create", result);

	if ((result = pthread_create(&tid2, NULL, thread_proc2, NULL)) != 0)
		exit_errno("pthread_create", result);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("%d\n", g_count);

	return 0;
}

void *thread_proc1(void *param)
{
	int i;

	for (i = 0; i < 1000000; ++i)
		__sync_fetch_and_add(&g_count, 1);
    
	return NULL;
}

void *thread_proc2(void *param)
{
	int i;

	for (i = 0; i < 1000000; ++i)
		__sync_fetch_and_add(&g_count, 1);
    
	return NULL;
}

void exit_errno(const char *msg, int result)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(result));

	exit(EXIT_FAILURE);
}