#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

//4. La linia de comandă se dau n argumente, primul va fi consider un string iar urmatoarele N-1
//vor fi considerate substringuri ce pot sa apara in stringul initial. 
//(n sa fie maxim 20, ca sa nu creati prea multe thread-uri). 
//Pentru fiecare substring se va crea un nou thread care va verifica daca 
//substringul respectiv apare in stringul principal si va incrementa o 
//variabila globala. La sfarsit programul principal va face printa aceasta variabila globala.

#define T_MAX 20
int sub_nr=0;
pthread_mutex_t muflex=PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    char* a1,*a2;
}pair;

void* count_sub(void* sub){
    pair* p=(pair*)sub;
    if (strstr(p->a1,p->a2)){
        pthread_mutex_lock(&muflex);
        sub_nr++;
        pthread_mutex_unlock(&muflex);
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t tid[T_MAX];
    if (argc<=2){
        printf("Too few args");
        return 0;
    }

    pair* pairs=(pair*)malloc((argc-1)*sizeof(pair));

    for (int i=1;i<argc-1;i++){
        pairs[i].a1=argv[1];
        pairs[i].a2=argv[i+1];
        pthread_create(&tid[i-1],NULL,count_sub,(void*)&pairs[i]);
    }

    for (int i=1;i<argc-1;i++){
        pthread_join(tid[i-1],NULL);
    }
    printf("Found %d substrings in the main string\n",sub_nr);
    free(pairs);
    pthread_mutex_destroy(&muflex);    
    return 0;
}