#ifndef __ASK2__
#define __ASK2__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>


union semun {
	int val;
	struct semid_ds *buffer;
	unsigned short *array;
	struct seminfo *__buffer;
};

typedef struct {
	unsigned int trace;
	char type_trace[1];
} mystruct;

void check(int argc,char *argv[],int *k,int *frames,int *q,int *max);
int down(int semid,int sem_number);
int up(int semid,int sem_number);
int setSemToX(int semid,int value,int sem_number);
int hash_function(int x, int numBuckets);

#endif
