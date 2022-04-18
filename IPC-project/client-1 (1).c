#include <stddef.h>
#include<string.h>
#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "shared_mem.h"

struct shm_data *p;
char temp[NUMBER_OF_MSG];
void *threadget() {
    while (1){
		
		
        pthread_mutex_lock(&p->s2c.mutex);
        while (p->s2c.front == p->s2c.tail){
			pthread_cond_wait(&p->s2c.empty, &p->s2c.mutex);
        }
        printf("%s", p->s2c.messages[p->s2c.front % NUMBER_OF_MSG]);
		fflush(stdout);
        p->s2c.front++;
        pthread_cond_signal(&p->s2c.full);
        pthread_mutex_unlock(&p->s2c.mutex);
		
		
	}
}

void *threadput() {
    while (1){
		
		
        while (fgets(temp, 1024, stdin)){

            pthread_mutex_lock(&p->c2s.mutex);

            while ((p->c2s.tail - p->c2s.front) == NUMBER_OF_MSG){
				pthread_cond_wait(&p->c2s.full, &p->c2s.mutex);
            }
            strcpy(p->c2s.messages[p->c2s.tail % NUMBER_OF_MSG], temp);
			p->c2s.tail++;
            pthread_cond_signal(&p->c2s.empty);
            pthread_mutex_unlock(&p->c2s.mutex);
		}
    }
}


int main(int argc, char *argv[]){

	int key;
	key	= atoi(argv[1]);
	puts("Shared memory achieved.");
	
	int shmid = shmget(key, sizeof(struct shm_data), 0666);	//Create shared memory ID
	if (shmid == -1) {
      puts("Failure in shared memory.");
      return -1;
   }
	
	p = (struct shm_data*)shmat(shmid, NULL, 0); 	//A pointer that also points to the other program's stucture.
	if (p == (void *) -1) {
      puts("Failure in attaching to shared memory.");
      return -1;
   }
   
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, threadget, &p);
	pthread_create(&tid2, NULL, threadput, &p);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}