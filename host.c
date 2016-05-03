#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include "sem.h"

/*-----------------------------------------INITIALIZATION OF VARIABLES-------------------------------------------*/
char param[10],param1[10],param2[10];

semaphore_t *semap;

int N, M, i;

char sem_name[30], mut_name[30],sem_bar_name[30];

void s_init(int);

/******************************************************************************************************************/







int  main(int argc, char *argv[])


{
	
	 N= atoi(argv[1]);
	 M= atoi(argv[2]);
	 pid_t pid, pids[20];
	 strcpy(sem_bar_name, "/tmp/sem_bar");
         semap = semaphore_create(sem_bar_name,N);
	 s_init(-1);  
         int j;
         for (j = 0; j < N; j++)
         {
             s_init(j);
         }


	for(i=0;i<N;++i)
  	{
   		 pid = fork();
    		 if(pid==0)
    		{
      			      sprintf(param1, "%d", M);
			      sprintf(param2, "%d", N);
			      sprintf(param, "%d", i);
			      execl("./philosopher","philosopher",param,param1,param2,(char *)0);		
      			      _exit(0);
   	        }
    		else if(pid>0)
  	        {
      		
     		            pids[i] = pid;
			    printf("the philosopher%d and its pid%d\n",i,pids[i]);
                    
                }
                else
                {
     		    perror("fork");
                    _exit(0);
   	        }
       }
  
  	for(i=0;i<N;++i) waitpid(pids[i],NULL,0);	
	return 0;


}



/*******************************function defination**************************************/


void s_init(int p) {
  
  if(p>=0){ 
    char p_fix[5];
    snprintf(p_fix,5,"%d",p);
    strcpy(sem_name,"/tmp/semaphore");
    strcat(sem_name, p_fix);        
    semap = semaphore_create(sem_name,0);   
  } 
  else if(p<0) {  /*-- Create Mutex --*/    
    strcpy(mut_name, "/tmp/mutex");
    semap = semaphore_create(mut_name,1);           
  }
  
  if (semap == NULL)
    exit(1);
  semaphore_close(semap);
}
/*---------------------------------------------------------------------------------------------*/
