#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/uio.h>
#include <fcntl.h>

#define N 10000
#define T 10
#define R 1000 // R*T=N
int v[N],s;
pthread_mutex_t m_s=PTHREAD_MUTEX_INITIALIZER;


void* do_sum(void* a){
    int* arr=(int*)a;
    for (int i=0;i<R;i++){
        if (arr[i]>0 && arr[i]%7==0 && arr[i]%2==0){
            pthread_mutex_lock(&m_s);
            s+=arr[i];
            pthread_mutex_unlock(&m_s);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){
    FILE* file_d;
    pthread_t tid[T];
    file_d=fopen("random-file.bin","rb");

    for (int i=0;i<N;i++){
        fread(&v[i],1,1,file_d);
    }
    fclose(file_d);
    for (int i=0;i<T;i++){
        pthread_create(&tid[i],NULL,do_sum,(void*)&v[i*R]);
    }
    for (int i=0;i<T;i++){
        pthread_join(tid[i],NULL);
    }
    
    printf("The total sum of elements that respect property is %d \n",s);
    pthread_mutex_destroy(&m_s);
    
    return 0;
}