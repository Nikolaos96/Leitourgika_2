/* Askisi 2 */
#include "ask2.h"

void check(int argc,char *argv[],int *k,int *frames,int *q,int *max){
    char *arg;


    if(argc != 9 ){
        printf("\nError in arguments command line. \n\n");
        exit(EXIT_FAILURE);
    }

    while(--argc){
        arg = *++argv;
        if(!strcmp(arg, "k"))           { if(argc > 1) *k = atoi(*++argv);      }
        else if(!strcmp(arg, "frames")) { if(argc > 1) *frames = atoi(*++argv); }
        else if(!strcmp(arg, "q"))      { if(argc > 1) *q = atoi(*++argv);      }
        else if(!strcmp(arg, "max"))    { if(argc > 1) *max = atoi(*++argv);    }

        if(argc > 1) argc--;
    }

    if((int)*max > 1000000){
        printf("\nError in arguments command line. \n\n");
        exit(EXIT_FAILURE);
    }

    int x = (int)(*max)/(int)(*q);
    *max = x;

    int val = (int)*q, val_2 = (int)*max;
    int val_3 = (int)*k, val_4 = (int)*frames;

    if((val * val_2) > 1000000 || (val * val_2) <= 0 || 2*val_3 > val_4 || val_4 <= 0 || val_3 <= 0 ){
        printf("\nError in arguments command line. \n\n");
        exit(EXIT_FAILURE);
    }

    return;
}


int down(int semid,int sem_number){
    struct sembuf sem_b;

    sem_b.sem_op = -1; /*down sem by 1*/
    sem_b.sem_num = sem_number;
    sem_b.sem_flg = 0;
    if (semop(semid,&sem_b, 1) == -1) printf("Semaphore_down failed\n");
    return 1;
}


int up(int semid,int sem_number){
    struct sembuf sem_b;

    sem_b.sem_op = 1; /*up sem by 1*/
    sem_b.sem_num = sem_number;
    sem_b.sem_flg = 0;
    if (semop(semid,&sem_b, 1) == -1) printf("Semaphore_up failed\n");
    return 1;
}


int setSemToX(int semid,int value,int sem_number){
    union semun sem;

    sem.val = value;
    if(semctl(semid,sem_number, SETVAL,sem) == -1) fprintf(stderr, "Semaphore_set_value failed   \n");
    return 1;
}


int hash_function(int x, int numBuckets){
    int a = 123, b = 432;
    int p = 79426549;

    return ( (a*x + b) % p ) % numBuckets;
}

