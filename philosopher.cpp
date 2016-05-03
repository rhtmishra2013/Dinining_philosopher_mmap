#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <cstdlib>

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>

struct shared_data {
  sem_t mutex;
  sem_t barrier;
  sem_t phil[10];
  int state[10];
};

struct shared_data *shared;

//int state[10];
//sem_t mutex;
//sem_t phil[10];

void take_fork(int ph_num,int N);
void test(int ph_num,int N);
void put_fork(int ph_num,int N);

void philosopher(int i,int M,int N)
{
	int j=0;
	while(j < M)
	{

	//sem_wait(&shared->mutex);
        sleep(1);
	//std::cout<<"hello"<<"by"<<i<<std::endl;
	std::cout<<"philosopher"<<i<<"is"<<"thinking"<<std::endl;
        take_fork(i,N);
        sleep(0);
        put_fork(i,N);
	j++;
	
	sem_wait(&shared->barrier);
        sem_post(&shared->barrier);
	}

	//std::cout<<j<<std::endl;
}

void take_fork(int ph_num,int N)
{
    sem_wait(&shared->mutex);
    shared->state[ph_num] = 1;
    //printf("Philosopher %d is Hungry\n",ph_num+1);
     std::cout<<"philosopher" <<ph_num<<"is Hungry"<<std::endl;
    test(ph_num,N);
    sem_post(&shared->mutex);
    sem_wait(&shared->phil[ph_num]);
    sleep(1);
}
  
void test(int ph_num,int N)
{
    if (shared->state[ph_num] == 1 && shared->state[(ph_num-1+N)%N] != 2 && shared->state[(ph_num+1)%N] != 2)
    {
        shared->state[ph_num] = 2;
        sleep(2);
        //printf("Philosopher %d takes fork %d and %d\n",ph_num+1,LEFT+1,ph_num+1);
	std::cout<<"philosopher"<<ph_num<<"is eating"<<std::endl;
        //printf("Philosopher %d is Eating\n",ph_num+1);
        sem_post(&shared->phil[ph_num]);
    }
}
  
void put_fork(int ph_num,int N)
{
    sem_wait(&shared->mutex);
    shared->state[ph_num] = 0;
    //printf("Philosopher %d putting fork %d and %d down\n",ph_num+1,LEFT+1,ph_num+1);
    //printf("Philosopher %d is thinking\n",ph_num+1);
    std::cout<<"Philosopher"<<ph_num<<"is thinking";
    test((ph_num-1+N)%N,N);
    test((ph_num+1)%N,N);
    sem_post(&shared->mutex);
}










void initialize_shared(int N)
{
  int i;
  int prot=(PROT_READ|PROT_WRITE);
  int flags=(MAP_SHARED|MAP_ANONYMOUS);
  shared= static_cast<shared_data*>(mmap(0,sizeof(*shared),prot,flags,-1,0));
  memset(shared,'\0',sizeof(*shared));
  sem_init(&shared->mutex,1,1);
  sem_init(&shared->barrier,1,N);
  for(i=0;i<N;++i) sem_init(&shared->phil[i],1,0);
}


void finalize_shared(int N)
{
  int i;
  for(i=0;i<N;++i) sem_destroy(&shared->phil[i]);
  munmap(shared, sizeof(*shared));
}

using namespace std;

int  main(int argc, char *argv[])


{
	int i;
	int N= atoi(argv[1]);
	int M= atoi(argv[2]);
	pid_t pid, pids[20];
	struct shared_data data;
	shared=&data;
	for(i=0;i < N;i++)
	{
		shared->state[i]=0;
        }	
	initialize_shared(N);

	
	for(i=0;i<N;++i)
  	{
   		 pid = fork();
    		 if(pid==0)
    		{
      			
      			philosopher(i,M,N);
			
      			_exit(0);
   	        }
    		else if(pid>0)
  	        {
      		
     		    pids[i] = pid;
                    cout<<i<<" "<<pids[i]<<endl;
                }
               else
                {
     		    perror("fork");
                    _exit(0);
   	        }
       }
  
  	for(i=0;i<N;++i) waitpid(pids[i],NULL,0);
	finalize_shared(N);
	return 0;


}

