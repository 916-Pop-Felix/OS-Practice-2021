#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define T 10
#define MAX 150
#define MIN 50
int c2,c3;
pthread_mutex_t m2=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3=PTHREAD_MUTEX_INITIALIZER;

void* count(void* a){
   
    int r;
    while(1){
        pthread_mutex_lock(&m2);
        if (c2>=5){
            pthread_mutex_unlock(&m2);
            break;
        }
        r=(rand() % (MAX + 1 - MIN)) + MIN;
        
        if (r<100){
            c2++;
            
        }
        pthread_mutex_unlock(&m2);
        if (r/100>0){
            pthread_mutex_lock(&m3);
            c3++;
            pthread_mutex_unlock(&m3);
        }
       printf("%d ",r);
            
    }
    return NULL;
}

int main(int argc, char* argv[]){
    srand(time(NULL) );
    pthread_t tid[T];
    for (int i=0;i<T;i++){
        pthread_create(&tid[i],NULL,count,NULL);
    }
    for (int i=0;i<T;i++){
        pthread_join(tid[i],NULL);
    }
    printf("%d numbers with 2 digits and %d numbers with 3\n",c2,c3);
    pthread_mutex_destroy(&m2);
    pthread_mutex_destroy(&m3);
    return 0;
}