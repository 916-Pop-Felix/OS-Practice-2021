#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

/*Se dau N numere separate ca argumente din consola.
 Se cere sa se afiseze tabela cu frecventa cifrelor.*/
 
pthread_mutex_t m[10];
int freq[10];

void* count_freq(void* a){
    char* new=a;
    for (int i=0;i<strlen(new);i++){
        if (isdigit(new[i])){
            pthread_mutex_lock(&m[new[i]-'0']);
            freq[new[i]-'0']++;
            pthread_mutex_unlock(&m[new[i]-'0']);
        }
    }
    return NULL;
}


 int main(int argc, char* argv[]){
    pthread_t tid[argc-1];
    if (argc<2){
        printf("Invalid number of args!\n");
        return 0;
    }
    for (int i=1;i<argc;i++){
        pthread_create(&tid[i-1],NULL,count_freq,(void*)argv[i]);
    }
    for (int i=1;i<argc;i++){
        pthread_join(tid[i-1],NULL);
    }
    for (int i=0;i<10;i++){
        printf("%d has %d apparitions\n",i,freq[i]);
    }
    for (int i=0;i<10;i++){
        pthread_mutex_destroy(&m[i]);
    }
    return 0;
 }