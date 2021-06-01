#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>


//* Write a program that creates N threads (N command line argument), passing as an argument to each thread
 //* a number and a string that are read from keyboard.
// * Threads sleep for 2 seconds, then they add the number to one of the global lists of numbers: 
// multiples of 7 or not * while for each string they store it in a global array of strings
 //* The main thread prints at the end the values of the global variables
 //* Ensure that no more than 4 therads are running at the same time
 //* The threads must be dinamically allocated in memory
 //* Ensure there are no memory leaks
// * Use efficient synchronization methods


pthread_mutex_t mw7=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mwo7=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mstr=PTHREAD_MUTEX_INITIALIZER;
int w7[100],wo7[100],cw7,cwo7,cstr;
char str[30][100];

pthread_barrier_t mybarrier;

typedef struct {
    int n1;
    char n2[30];
} pair;

void* threadFn(void *nms) {
    pair* pp=(pair*)nms;

    printf("thread %d: ", pp->n1);
   
    sleep(2);
    printf("thread %d: I'm ready...\n", pp->n1);
    
    pthread_barrier_wait(&mybarrier);
    if (atoi(pp->n2)){
        int n=atoi(pp->n2);
        if (n%7==0){
            pthread_mutex_lock(&mw7);
            w7[cw7++]=n;
            pthread_mutex_unlock(&mw7);
        }
        else{
            pthread_mutex_lock(&mwo7);
            wo7[cwo7++]=n;
            pthread_mutex_unlock(&mwo7);
        }
    }
    else{
        pthread_mutex_lock(&mstr);
        strcpy(str[cstr++],pp->n2);
        pthread_mutex_unlock(&mstr);
    }
    printf("thread %d: incremented!\n", pp->n1);

    return NULL;
}

int main(int argc, char** argv) {
    int i;
    pthread_t ids[argc];
    srand(time(NULL));
    pair p[100];
    if ( (argc-1)%2){
        printf("Error\n");
        return 0;
    }
    pthread_barrier_init(&mybarrier, NULL, 3);
    
    for (i=1; i < argc; i++) {
        p[i-1].n1=i-1;
        strcpy(p[i-1].n2,argv[i]);
        pthread_create(&ids[i-1], NULL, threadFn, (void*)&p[i-1]);
    }


    for (i=1; i < argc; i++) 
        pthread_join(ids[i-1], NULL);
    
    pthread_barrier_destroy(&mybarrier);
    pthread_mutex_destroy(&mstr);
    pthread_mutex_destroy(&mw7);
    pthread_mutex_destroy(&mwo7);

    for (int i=0;i<cw7;i++){
        printf("%d ",w7[i]);
    }
    printf("\n");
    for (int i=0;i<cwo7;i++){
        printf("%d ",wo7[i]);
    }
    printf("\n");
    for (int i=0;i<cstr;i++){
        printf("%s ",str[i]);
    }
    printf("\n");
    return 0;
}
