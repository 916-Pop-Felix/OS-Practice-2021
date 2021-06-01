#include <pthread.h>
#include <stdio.h>
#define T 10
pthread_cond_t idx;
pthread_mutex_t midx=PTHREAD_MUTEX_INITIALIZER;
int n_id;
int v[T];
void* f(void* a){
    int i=*(int*)a;
    
    //while(1){
        pthread_mutex_lock(&midx);
        //printf("Thread %d entered\n",i);
        while(i!=n_id){
            pthread_cond_wait(&idx,&midx);
        }
        printf("Thread %d executed\n",i);
        n_id++;
        //if (n_id>=T){
        //    n_id=0;
        //}
        pthread_cond_broadcast(&idx);
        pthread_mutex_unlock(&midx);
    //}
    return NULL;
}

int main(int argc, char** argv){
    pthread_t tid[T];
    for (int i=0;i<T;i++){
        v[i]=i;
        pthread_create(&tid[i],NULL,f,(void*)&v[i]);
    }
    for (int i=0;i<T;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&midx);
    return 0;
}