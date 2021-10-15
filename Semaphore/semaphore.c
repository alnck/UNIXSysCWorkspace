#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>s
#include <semaphore.h>

void *thread_proc1(void* param);
void *thread_proc2(void* param);
void do_machine(const char* name);
void exit_sys(const char *msg);
void exit_errno(const char* msg, int result);

sem_t g_sem;

int main(int argc, char *argv[])
{
	int result;
	pthread_t tid1, tid2;

	srand(time(NULL));

	if (sem_init(&g_sem, 0, 1) == -1)
		exit_sys("sem_init");

	if ((result = pthread_create(&tid1, NULL, thread_proc1, NULL)) != 0)
		exit_errno("pthread_create", result);

	if ((result = pthread_create(&tid2, NULL, thread_proc2, NULL)) != 0)
		exit_errno("pthread_create", result);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	sem_destroy(&g_sem);

	return 0;
}

void *thread_proc1(void *param)
{
	int i;

	for (i = 0; i < 10; ++i)
		do_machine("thread-1");

	return NULL;
}

void *thread_proc2(void *param)
{
	int i;

	for (i = 0; i < 10; ++i)
		do_machine("thread-2");

	return NULL;
}

void do_machine(const char *name)
{
	if (sem_wait(&g_sem) == -1)
		exit_sys("sem_wait");

	printf("---------------\n");
	printf("1) %s\n", name);
	usleep(rand() % 300000);
	printf("2) %s\n", name);
	usleep(rand() % 300000);
	printf("3) %s\n", name);
	usleep(rand() % 300000);
	printf("4) %s\n", name);
	usleep(rand() % 300000);
	printf("5) %s\n", name);
	usleep(rand() % 300000);

	if (sem_post(&g_sem) == -1)
		exit_sys("sem_post");
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

void exit_errno(const char *msg, int result)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(result));

	exit(EXIT_FAILURE);
}