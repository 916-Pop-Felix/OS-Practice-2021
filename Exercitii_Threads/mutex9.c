#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int c_v,*v;
pthread_mutex_t m_v=PTHREAD_MUTEX_INITIALIZER;

void* gen_num(void* num){
    int id=*(int*) num;
    printf("%d: ",id);
    int r1=rand()%1000;
    printf("%d ",r1);
    if (r1>=100 && r1<1000){
        pthread_mutex_lock(&m_v);
        v[c_v++]=r1;
        pthread_mutex_unlock(&m_v);
    }
    int r2=rand()%1000;
    printf("%d\n",r2);
    if (r2>=100 && r2<1000){
        pthread_mutex_lock(&m_v);
        v[c_v++]=r2;
        pthread_mutex_unlock(&m_v);
    }
    return NULL;
}

int main(int argc, char* argv[]){
    int n=atoi(argv[1]);
    v=(int*)malloc(n*2*sizeof(int));
    pthread_t tid[n];
    for (int i=0;i<n;i++){
        
        pthread_create(&tid[i],NULL,gen_num,(void*)&i);
    }
    for (int i=0;i<n;i++){
        pthread_join(tid[i],NULL);
    }
    for (int i=0;i<c_v;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    pthread_mutex_destroy(&m_v);
    free(v);
    return 0;
}