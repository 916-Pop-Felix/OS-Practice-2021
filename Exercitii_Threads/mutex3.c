#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//3. Write a program that creates 20 threads, giving each thread a string as parameter. Each thread will count and add to the 
//global variables v and n as follows: the number of vowels contained by the string added to v, 
//and the number of digits contained in the string added to n. Synchronise threads using mutex and check 
//for memory leaks.

int v,n;
pthread_mutex_t m_v=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_n=PTHREAD_MUTEX_INITIALIZER;

int voc(char a){
    if (strchr("aeiouAEIOU",a)!=0)
        return 1;
    return 0;
}

void* thrf(void* ch){
    char* new=ch;
    for (int i=0;i<strlen(new);i++){
        if (voc(new[i])){
            pthread_mutex_lock(&m_v);
            v++;
            pthread_mutex_unlock(&m_v);
        }
        if (isdigit(new[i])){
            pthread_mutex_lock(&m_n);
            n++;
            pthread_mutex_unlock(&m_n);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t tid[argc-1];
    for (int i=1;i<argc;i++){
        if(pthread_create(&tid[i-1],NULL,thrf,(void*)argv[i])!=0){
            perror("Bad thread");
            exit(1);
        }
    }
    for (int i = 1; i < argc; i++){
        pthread_join(tid[i-1],NULL);
    }
    printf("Counted a total number of %d vowels and %d digits\n",v,n);
    pthread_mutex_destroy(&m_v);
    pthread_mutex_destroy(&m_n);
    return 0;
}