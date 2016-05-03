#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include "sem.h"
 
#define THINKING 0
#define HUNGRY 1
#define EATING 2

semaphore_t *semap;
int N, M, p;


char sem_name[30], mut_name[30],sem_bar_name[30];

void think(int);
void eat(int);
void take_forks(int);
void put_forks(int);
void test(int);
void s_wait();
void s_post();
void update_state(int);
int check_state(int);
void b_wait();
char get_sem(int);

int main(int argc, char* argv[]) {	
	
	N = atoi(argv[3]);
 	M = atoi(argv[2]);
 	p= atoi(argv[1]);	
 	int count = M;
	
	strcpy(mut_name, "/tmp/mutex");
	strcpy(sem_bar_name,"/tmp/sem_bar");
	char p_fix[5];
	snprintf(p_fix,5,"%d",p);
	strcpy(sem_name,"/tmp/semaphore");
	strcat(sem_name, p_fix);	
	int j=0;
	s_wait(sem_bar_name);
	while (j < M) 
       {	
		
			
		think(p); 		
		take_forks(p);   
		sleep(0);			
		put_forks(p);
		j++;		
		s_post(sem_bar_name);
	        	
	}

	
	exit(0);
}																																																																															





void think(int p) {
	
	update_state(THINKING);
	printf("Philosopher %d: THINKING\n",p);
	sleep(1);
}

void eat(int p) {
	update_state(EATING);
	printf("Philosopher %d: EATING\n",p);
	sleep(1);
}



void take_forks(int p){

	s_wait(mut_name);
	update_state(HUNGRY);
	printf("Philosopher %d: HUNGRY\n",p);
	test(p); 
	s_post(mut_name);	
	s_wait(sem_name); 
	
}

void test(int p) {	
	if ( check_state(p) == HUNGRY && check_state((p+N-1)%N) != EATING && check_state((p+1)%N ) != EATING ) {
		sleep(2);
		eat(p);
		char p_fix[5];
		snprintf(p_fix,5,"%d",p);
		char temp_name[30];																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													
		strcpy(temp_name,"/tmp/semaphore");
		strcat(temp_name, p_fix);		
		s_post(temp_name);
	}
}

int check_state(int p) {
	int value;
	char p_fix[5];
	snprintf(p_fix,5,"%d",p);
	char temp_name[30];	
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									 strcpy(temp_name,"/tmp/semaphore");
	strcat(temp_name, p_fix);		
	semap = semaphore_open(temp_name);
	value = semap->state;
	semaphore_close(semap);
	return value;
}
	
void put_forks(int p) {
	s_wait(mut_name);
	update_state(THINKING);
	sleep(1);
	test((p+N-1)%N );
	test((p+1)%N );
	s_post(mut_name);
}




void s_wait(char* str) {
	semap = semaphore_open(str);
	if (semap == NULL)
		exit(1);
	semaphore_wait(semap);
	semaphore_close(semap);
}

	

void s_post(char* str) {
	semap = semaphore_open(str);
	if (semap == NULL)
		exit(1);
	semaphore_post(semap);
	semaphore_close(semap);
}

void update_state(int x) {
	semap = semaphore_open(sem_name);
	if (semap == NULL)
		exit(1);
	semap->state = x;	
	semaphore_close(semap);
}





	


	
