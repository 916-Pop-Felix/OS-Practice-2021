#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t fmtx=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t dmtx=PTHREAD_MUTEX_INITIALIZER;
int f,d;

void* check_file_dir(void* n){
    char res[10];
    char name[100];
    strcpy(name,(char*)n); 
    DIR* dir=opendir(name);
    if (dir){
            pthread_mutex_lock(&dmtx);
            strcpy(res,"dir");
            d++;
            pthread_mutex_unlock(&dmtx);
        }
    else{
        FILE* fd;
        if ((fd=fopen(name,"r"))){
            pthread_mutex_lock(&fmtx);
            strcpy(res,"file");
            f++;
            pthread_mutex_unlock(&fmtx);
        }
        else{
            strcpy(res,"other");
        }
    }
    return NULL;
}

int main(int argc, char** argv){
    pthread_t tid[argc];
    for (int i=1;i<argc;i++){
        pthread_create(&tid[i-1],NULL,check_file_dir,(void*)argv[i]);
    }
    for (int i=1;i<argc;i++){
        pthread_join(tid[i-1],NULL);
    }
    printf("There are %d files and %d directories\n",f,d);
    pthread_mutex_destroy(&fmtx);
    pthread_mutex_destroy(&dmtx);
    return 0;
}