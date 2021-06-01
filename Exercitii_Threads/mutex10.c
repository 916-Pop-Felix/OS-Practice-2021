#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int asci_table[128];

pthread_mutex_t m_ascii=PTHREAD_MUTEX_INITIALIZER;

void* f(void* a){
    char new[100];
    strcpy(new,(char*)a);
    for (int i=0;i<strlen(new);i++){
        pthread_mutex_lock(&m_ascii);
        asci_table[(int)new[i]]++;
        pthread_mutex_unlock(&m_ascii);
    }
    return NULL;
}

int main(int argc, char** argv){
    if (argc<3){
        printf("Not enough args");
        return 0;
    }
    pthread_t tid[argc];
    for (int i=1;i<argc;i++){
        pthread_create(&tid[i-1],NULL,f,(void*)argv[i]);
    }
    for (int i=1;i<argc;i++){
        pthread_join(tid[i-1],NULL);
    }
    for (int i=0;i<128;i++){
        printf("%c has frequency %d\n",i,asci_table[i]);
    }
    pthread_mutex_destroy(&m_ascii);
    return 0;
}