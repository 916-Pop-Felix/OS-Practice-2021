#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//2. Write a program that creates 4 threads and had 3 global variables v5, v2, v3.
//Each thread generates a random number and:
//- if the number is multiple of 2 increments v2
//- if the number is multiple of 3, increments v3
//- if the number is multiple of 5 increments v5

pthread_mutex_t m_v2=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_v3=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_v5=PTHREAD_MUTEX_INITIALIZER;
int v2,v3,v5;

void* count(void* unused){
    int r=*(int*) unused;
     printf("%d\n",r);
    if (r%2==0){
        pthread_mutex_lock(&m_v2);
        v2++;
        pthread_mutex_unlock(&m_v2);
    }
    if (r%3==0){
        pthread_mutex_lock(&m_v3);
        v3++;
        pthread_mutex_unlock(&m_v3);
    }
    if (r%5==0){
        pthread_mutex_lock(&m_v5);
        v5++;
        pthread_mutex_unlock(&m_v5);
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t tid[4];
    int r;
    srand(time(0));
    for (int i=0;i<4;i++){
        r=rand();
        //printf("%d\n",r);
        pthread_create(&tid[i],NULL,count,(void*)&r);
    }
    for (int i=0;i<4;i++){
        pthread_join(tid[i],NULL);
    }
    printf("Divizibil cu 2: %d\n",v2);
    printf("Divizibil cu 3: %d\n",v3);
    printf("Divizivil cu 5: %d\n",v5);

    pthread_mutex_destroy(&m_v2);
    pthread_mutex_destroy(&m_v3);
    pthread_mutex_destroy(&m_v5);
    return 0;
}