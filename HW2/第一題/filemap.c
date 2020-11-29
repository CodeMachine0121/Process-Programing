#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<string.h>
#include<err.h>
#include<time.h>

#define BUFFER_SIZE 1000
#define ALLOC_SIZE (100*1024*1024)//100mb

static char command[BUFFER_SIZE];
static char file_contents[BUFFER_SIZE];
static char overwirte_data[]="hello After\n";

int main(void){
    clock_t before,after;
    pid_t pid;
    pid = getpid();
    //snprintf(command, BUFFER_SIZE,"cat /proc/%d/maps",pid);

    //puts("*** memory map before mapping file ***");
    //fflush(stdout);
    system(command);

    before = clock();

    int fd;
    fd = open("testfile",O_RDWR);
    if(fd==-1){
        err(EXIT_FAILURE,"open() failed");
    }

    char *file_contents;
    file_contents = mmap(NULL,ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
/*
    if(file_contents==(void*)-1){
        warn("mmap() failed");
        goto close_file;
    }
*/

    puts("");
    printf("*** succeeded to map file: address = %p; size = %x  ***\n",file_contents,ALLOC_SIZE);

    puts("");
    puts("*** memory map after mapping file ***");

    fflush(stdout);
    system(command);


    puts("");
    printf("file contents before overwirte mapped region: %s \n",file_contents);
    /// overwrite mapped region 
    memcpy(file_contents, overwirte_data, strlen(overwirte_data));

    //puts("");
    //printf("*** overwritten mapped region with: %s\n",file_contents);
    
    after = clock();
    printf("file contents after overwirte mapped region: %s \n",file_contents);
    printf("time: %ld\n",after-before);

    //解除映射關係
    munmap(file_contents, ALLOC_SIZE);
/*  if(munmap(file_contents, ALLOC_SIZE) == -1){
        warn("munmap() failed");
    }
*/


close_file:
    if(close(fd)==-1){
        warn("close() failed");
    }    

    exit(EXIT_FAILURE);
}
