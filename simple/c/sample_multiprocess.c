#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <stdlib.h>


#include <stdio.h>
#include <unistd.h>


void* DummyFunc(int pid)
{
    int sum=0;
    unsigned int cpu, node;
    for( int i=0; i<100000; i++)
        for( int j=0; j<100000; j++)
            sum += i*j;
    getcpu(&cpu, &node);
    printf("pid= %d, cpu = %d, node=%d\n",pid, cpu, node);

}

int main()
{
    pid_t pids[10];
    int i;
    int n = 10;

    /* Start children. */
    for (i = 0; i < n; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            DummyFunc(pids[i]);
            exit(0);
        }
    }

    /* Wait for children to exit. */
    int status;
    pid_t pid;
    while (n > 0) {
        pid = wait(&status);
        printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
        --n;  // TODO(pts): Remove pid from the pids array.
    } 
}