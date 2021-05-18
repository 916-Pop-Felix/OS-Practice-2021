#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//2. Solve the problem of adding 4 numbers in parallel, but using two threads – one that calculates the
//sum of first two, another that calculated the sum of last two, and main program receives the
//calculated values and uses the partial sums to compute the total sum. For the return value we use
//pthread_exit and pthread_join (second argument) together with a pointer to a
//return_val which can be, as in our case, a struct.
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
int a[]={1,2,3,4};
int s=0;

void* partial_sum(void* idx){
    int nr=*(int*)idx;
    int ps=a[nr*2]+a[nr*2+1];
    pthread_mutex_lock(&m);
    s+=ps;
    pthread_mutex_unlock(&m);    
}

int main(int argc, char* argv[]){
    int tnr[2];
    tnr[0]=0;
    tnr[1]=1;
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,partial_sum,(void*)&tnr[0]);
    pthread_create(&tid[1],NULL,partial_sum,(void*)&tnr[1]);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    printf("Suma celor 4 numere este %d",s);
    pthread_mutex_destroy(&m);
    return 0;
}