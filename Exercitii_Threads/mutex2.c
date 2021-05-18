#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1. Write a program that receives strings as command line arguments and uses threads to capitalise
//each word. We’ll create for each argument a separate thread that will capitalise the initial letter.

void* fullcap(void* ch){
    char new[100];
    strcpy(new,(char*)ch);
    if (new[0]>='a' && new[0]<='z'){
        new[0]+='A'-'a';
    }
    printf("%s ",new);
}

int main(int argc, char *argv[]){
    pthread_t tid[argc];
    
    for (int i=0;i<argc-1;i++)
        pthread_create(&tid[i],NULL,fullcap,(void*)argv[i+1]);
    for (int i=0;i<argc-1;i++)
        pthread_join(tid[i],NULL);
    printf("\n");
    return 0;
}