#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void){

    char file_contents[1024];
    clock_t before,after;

    before = clock();

    FILE* ptr = fopen("./testfile","r+");
// read
    fread(file_contents,1024,1,ptr);
    printf("*** file contents before overwirte mapped region: %s\n",file_contents);
// write
    //fwrite(buf, strlen(buf), 1, file);
    freopen(NULL,"w+",ptr);
    fwrite("hello After\n",strlen("hello After\n"), 1, ptr);
// read
    freopen(NULL,"r+",ptr);
    fread(file_contents,1024,1,ptr);
    printf("*** file contents after overwirte mapped region: %s\n",file_contents);
    
    fclose(ptr);

    after = clock();
    printf("time: %ldms\n",after-before);
   


    return 0;
}