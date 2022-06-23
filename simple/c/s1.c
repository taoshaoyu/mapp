#include <stdio.h>
#include <unistd.h>
int main(){
    printf("1\n");
#if 1
    int sum=0;
    for( int i=0; i<100000; i++)
        for( int j=0; j<100000; j++)
            sum += i*j;
    printf("2 sum=%d\n",sum);
#else
    sleep(1);
#endif
    return 0;
}
