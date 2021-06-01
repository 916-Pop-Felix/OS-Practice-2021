#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_cond_t counter;
pthread_mutex_t mctr=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mrndm=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mapp_m=PTHREAD_MUTEX_INITIALIZER;
int N,c,M,v[6000],app_m;

void* thread1(void* a){
    FILE* f;
    f=fopen("num.txt","r");
    for (int i=0;i<N;i++){ 
        fread(&v[i],1,1,f);  
        pthread_mutex_lock(&mctr); 
        c++;
        pthread_mutex_unlock(&mctr);
    }
    M=rand()%256;
    pthread_cond_broadcast(&counter);
    fclose(f);
    return NULL;
}

void* thread2(void* a){
    pthread_mutex_lock(&mctr);
    if (c!=N){
        pthread_cond_wait(&counter,&mctr);
    }
    pthread_mutex_unlock(&mctr);
    int i=*(int*)a;
    int occ;
    for (int j=i*20;j<(i+1)*20;j++){
        if (v[j]==i){
            occ++;
        }
    }
    
    pthread_mutex_lock(&mapp_m);
    printf("%d has %d occurences in interval %d-%d\n",M,occ,i*20,(i+1)*20);
    app_m+=occ;
    pthread_mutex_unlock(&mapp_m);
    return NULL;
}

int main(int argc, char** argv){
    srand(time(NULL));
    pthread_t t1;
    N=atoi(argv[1]);
    
    int nthr2=N/20;
    pthread_t t2[nthr2];
    printf("%d\n",nthr2);
    pthread_create(&t1,NULL,thread1,NULL);
    //sleep(1);
    for (int i=0;i<nthr2;i++){
        pthread_create(&t2[i],NULL,thread2,(void*)&i);
    }
    pthread_join(t1,NULL);
    for (int i=0;i<nthr2;i++){
        pthread_join(t2[i],NULL);
    }
    pthread_mutex_destroy(&mctr);
    pthread_mutex_destroy(&mrndm);
    pthread_mutex_destroy(&mapp_m);
    printf("%d has a total num of occurences of %d\n",M,app_m);
    return 0;
}