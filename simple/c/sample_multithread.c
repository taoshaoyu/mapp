#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <stdlib.h>


/* function to be executed by the new thread */
void* DummyFunc(void* data)
{
    int my_data = (int)data;     	/* data received by thread */
    int sum=0;
    unsigned int cpu, node;

    pthread_detach(pthread_self());
    for( int i=0; i<100000; i++)
        for( int j=0; j<100000; j++)
            sum += i*j;
  //  printf("2 sum=%d\n",sum);
    getcpu(&cpu, &node);
    printf("cpu = %d, node=%d\n",cpu, node);
    pthread_exit(NULL);			/* terminate the thread */
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    int        t         = 11;  /* data passed to the new thread          */

    for( int n=0; n<10; n++){
      rc = pthread_create(&thread_id, NULL, DummyFunc, (void*)t);  
      if(rc)			
      {
          printf("\n ERROR: return code from pthread_create is %d \n", rc);
          exit(1);
      }
    }
    printf("\n Created new thread (%u) ... \n", thread_id);
    
    pthread_exit(NULL);		/* terminate the thread */
}