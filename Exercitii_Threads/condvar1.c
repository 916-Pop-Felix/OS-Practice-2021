#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//5. Vom create N thread-uri considerate consumatori, si M thread-uri considerate producatori.
//    Un producator va insera un numar de X mesaje (pot fi orice, numere, charactere etc.) 
//intr-o coada globala. De fiecare data cand coada se umple (adica atinge o limita L) producatorii vor trebui 
//sa astepte pana cand se elibereaza cel putin un loc in coada.
//    Un consumator va extrage mesaje din aceeasi coada globala. De fiecare data cand coada este goala, consumatorii
// vor trebui sa astepte pana cad se adauga cel putin un element. 
//    Se doreste implementarea acestor mecanisme de asteptare/notificare folosind variabile conditionale. 


pthread_mutex_t m_len=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c;

#define N 100
#define M 40
#define X 10
#define L 300
int count;


void* prod_action(void* a){
    while(1){
        pthread_mutex_lock(&m_len);
        while(count>L-X){
            pthread_cond_wait(&c,&m_len);
        }
        count+=X;
        printf("#->%d",count);
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m_len);
    }
    return NULL;
}

void* consum_action(void* a){
    while(1){
        pthread_mutex_lock(&m_len);
        while(count==0){
            pthread_cond_wait(&c,&m_len);
        }
        count--;
        printf("!%d",count);
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m_len);
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t prod[M];
    pthread_t consum[N];
    for (int i=0;i<M;i++){
        pthread_create(&prod[i],NULL,prod_action,NULL);
    }
    for (int i=0;i<N;i++){
        pthread_create(&consum[i],NULL,consum_action,NULL);
    }
    for (int i=0;i<M;i++){
        pthread_join(prod[i],NULL);
    }
    for (int i=0;i<N;i++){
        pthread_join(consum[i],NULL);
    }
    return 0;
}