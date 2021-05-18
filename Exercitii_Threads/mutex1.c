#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t gcd_m=PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int n1;
    int n2;
} pair;
int counter=0;

int gcd(int a, int b){
    while(b!=0){
        int r=a%b;
        a=b;
        b=r;
    }
    return a;
}

void* th(void* nms){
    pair* p=(pair*)nms;
    int a=p->n1;
    int b=p->n2;
    if (gcd(a,b)==1){
        pthread_mutex_lock(&gcd_m);
        counter++;
        pthread_mutex_unlock(&gcd_m);
    }
    return NULL;
} 

int main(int argc, char* argv[]){
    int n=argc-1;

    pair* pairs=(pair*)malloc(n*sizeof(pair));

    pthread_t thr[n];
    for (int i=1;i<n;i++){
        pairs[i].n1=atoi(argv[i]);
        pairs[i].n2=atoi(argv[i+1]);
        pthread_create(&thr[i],NULL,th,(void*)&pairs[i]);
    }
    for (int i=1;i<n;i++){
        pthread_join(thr[i],NULL);
    }
    printf("Gasit %d perechi prime intre ele\n",counter);
    pthread_mutex_destroy(&gcd_m);
    free(pairs);
    return 0;
}