#include <stdio.h>
#include <unistd.h>

int main(){
    int pagesize;
    pagesize=getpagesize();
    printf("pagesize = 0x%x\n",pagesize);
    return 0;
}
