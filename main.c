/* main.c */
#include <stdio.h>
#include "ask2.h"
#include "hash_table.h"

#define PROCESS 2
#define H_T_LEN 60	// Number of bucket hash table



int main(int argc, char *argv[]){
 int k, frames, q, Max;
 int pid, i, wpid, status;
 char *arg;

    check(argc,argv,&k,&frames,&q,&Max);  /* Check the argument in command line */

    int keyForSharedMemSpace = 11111;
    int sm_id;	/* Shared memory for communication manufacturers - dyers and dyers - controls */
    if((sm_id = shmget(keyForSharedMemSpace, sizeof(mystruct), 0666 | IPC_CREAT)) == -1){
	fprintf(stderr, "Failed shared memory (sm_id) \n");
	exit(EXIT_FAILURE);
    }
    mystruct *mptr = (mystruct*) shmat(sm_id, (void *)0, 0);

    int keyForSemaphore = 33333;
    int sem_id;	/* Semaphore set */
    if((sem_id = semget((key_t)keyForSemaphore, 5, IPC_CREAT | 0666)) == -1){ // 5
	fprintf(stderr, "Failed semaphores  \n");
	exit(EXIT_FAILURE);
    }

    /* Initialization of all the semaphores I created */
    setSemToX(sem_id,1,0);
    setSemToX(sem_id,0,1);
    setSemToX(sem_id,1,2);
    setSemToX(sem_id,1,3);
    setSemToX(sem_id,0,4);

    /* production of child processes */
    for(i = 0 ; i < PROCESS ; i++){
	pid = fork();
	if(pid) pid = 0;
	else{
	    pid = i+1;
	    break;
	}
    }

    /* PM1 - PM2 processes send requests */
    /* PP1 k=0 and m=1 | PM2 k=1 and m=0 */
    if(pid == 1 || pid == 2){
	FILE *f;
        unsigned int rv;
        char A[1];
	int k, m, stop = 0;
	if(pid == 1){ // PM1
            if ((f = fopen("gcc.trace","r")) == NULL){
            	fprintf(stderr, "File gcc.trace doesnt exist?! \n");
            	exit(EXIT_FAILURE);
            }
	    k = 0;
	    m = 1;
	}else{ // PM2
	    if ((f = fopen("bzip.trace","r")) == NULL){
                fprintf(stderr, "File bzip.trace doesnt exist?! \n");
                exit(EXIT_FAILURE);
            }
	    k = 1;
	    m = 0;
	}
 	while(Max-- > 0){
	    down(sem_id,k);		// if KM1 then k=0, m=1, if KM2 then k=1, m=0
    	    int rep = 0;
    	    while(rep++ < q){
        	if(fscanf(f, "%x", &rv) != 1){
		    stop = 1;
		    break;
		}
        	fscanf(f, "%s", &A[0]);
		down(sem_id,2);
		down(sem_id,3);

		mptr->trace = rv;	/* Write trace in shared memory */
	        strcpy(mptr->type_trace,A);

		up(sem_id,3);
		up(sem_id,4);
    	    }
   	    if(stop == 1) break;
	    up(sem_id,m);
  	}
        fclose(f);
	exit(EXIT_SUCCESS);
    }else if(pid == 0){ // ********************  MM  *******************************************
	FILE *f, *fd;
	if ((f = fopen("bzip.trace","r")) != NULL && (fd = fopen("gcc.trace","r")) != NULL){
	    int i;
	    unsigned int rv;
	    char A[1];
	    mystruct *memory = malloc(frames * sizeof(mystruct));		// Main memory
	    for(i = 0 ; i < frames ; i++) memory[i].trace = 0;			// Initially the memory is empty

	    info_deikti *list;                               			// Hashed Page Table
            list = malloc(H_T_LEN * sizeof(info_deikti));    			// Array of pointer in  head node
            for(i = 0 ; i < H_T_LEN ; i++) list[i] = LIST_dimiourgia(&list[i]); // Create Hash Table

	    int reads = 0, writes = 0, registers_traces = 0, xx = 0;
	    int number_of_frames = 0, pf_1 = 0, pf_2 = 0;
	    int rep = 2 * (q * Max), f, turn = 1, counter = 1;
	    unsigned int page_number;
	    char page_type[1];
	    int half_memory = frames/2;
	    int half_Hah_P = H_T_LEN /2;

	    if(rep > 2000000) rep = 2000000;

	    while(rep-- > 0){
	        down(sem_id,4);
	        down(sem_id,3);

		strcpy(page_type,mptr->type_trace);				// Read trace from shared memory
		page_number = mptr->trace;
		f = hash_function(page_number >> 12, half_Hah_P);		// Universal Hash Function

		if(turn % 2 != 0){ /* request from PM1*/
		    mystruct *page = anazitisi(&list[f],page_number >> 12);
	            if(page != NULL){
			// printf("The page is in memory. \n");
		    }else{
			pf_1++;
			reads++;
		    	int poss = -1;						// Find the position of a free frame
		    	for(i = 0 ; i < half_memory ; i++){			// in the memory
		             if(memory[i].trace == 0){
		    		poss = i;
		    		break;
	  		     }
			}
		    	if(pf_1 % (k+1) != 0){					// Main memory have free space and page faults
		    	    memory[poss].trace = page_number;			// not equals with k+1
		    	    strcpy(memory[poss].type_trace,page_type);
		      	    eisagogi(&list[f],page_number >> 12,&memory[poss]);
			}else{							// Page faults equals with k+1
			    pf_1++;
			    xx++;
			    for(i = 0 ; i < half_memory ; i++){			// Flush main memory
				if(!strcmp(memory[i].type_trace,"R")) writes++;
				memory[i].trace = 0;
			    }
			    for(i = 0 ; i < half_Hah_P ; i++) lista_diagrafi(&list[i]);
			    memory[0].trace = page_number;
		     	    strcpy(memory[0].type_trace,page_type);
		    	    eisagogi(&list[f],page_number >> 12, &memory[0]);
			}
		    }
		}else{  /* request from PM2 */
		    f = f + half_Hah_P;
		    mystruct *page = anazitisi(&list[f],page_number >> 12);
		    if(page != NULL){
                    //    printf("The page is in memory. \n");
                    }else{
		       pf_2++;
		       reads++;
                       int poss_2 = -1;
		       for(i = half_memory ; i < frames ; i++){			 // Find the position of a free frame
		           if(memory[i].trace == 0){				 // in the memory
		  	       poss_2 = i;
		    	       break;
			   }
		        }
		    	if(pf_2 % (k+1) != 0){					 // Main memory have free space and page faults
		    	    memory[poss_2].trace = page_number;			 // not equals with k+1
		     	    strcpy(memory[poss_2].type_trace,page_type);
		     	    eisagogi(&list[f],page_number >> 12,&memory[poss_2]);
			}else{							 // Page faults equals with k+1
			    pf_2++;
			    xx++;
			    for(i = half_memory ; i < frames ; i++){		 // Flush main memory
			        if(!strcmp(memory[i].type_trace,"R")) writes++;
				memory[i].trace = 0;
			    }
			    for(i = half_Hah_P ; i < H_T_LEN ; i++) lista_diagrafi(&list[i]);
	  		    memory[half_memory].trace = page_number;
		    	    strcpy(memory[half_memory].type_trace,page_type);
		    	    eisagogi(&list[f],page_number >> 12, &memory[half_memory]);
			}
                    }
		}
		if(counter++ == q){
                        turn++;
                        counter = 1;
                }

	        up(sem_id,3);
	        up(sem_id,2);
	    }

	    registers_traces = 2 * (Max * q);
	    for(i = 0 ; i < frames ; i++){			// Find all empty frames
                if(memory[i].trace == 0) number_of_frames++;
            }

	    printf("\nReads from disc : %d\nWrites on disc  : %d\n", reads, writes);
	    printf("Page faults     : %d (%d : PM1 | %d : PM2) \n", pf_1 + pf_2 - xx, pf_1-xx,pf_2);
	    printf("Crowd of traces : %d\n", registers_traces);
	    printf("Empty frames    : %d / %d  \n\n", number_of_frames, frames);

	    for(i = 0 ; i < H_T_LEN ; i++){			// Delete Hashed Page table and all lists
	        lista_diagrafi(&list[i]);			// Delete all linked lists
	        free(list[i]);					// Delete Hash Table
	    }
	    free(memory);					// Delete main Memory
        }
    }

    while ((wpid = wait(&status)) > 0); 			// Parent process wait all childs
    shmdt(mptr);						// Remove shared memory
    semctl(sem_id, 0, IPC_RMID);				// Remove semaphore set

    return 0;							// or exit(0) is the same
}
