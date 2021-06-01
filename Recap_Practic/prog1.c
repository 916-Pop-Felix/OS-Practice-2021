#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    char new[100];
    int n=0;
    for (int i=0;i<strlen(argv[1]);i++){
        if(!strchr("AEIOUaeiou",argv[1][i])){
            new[n]=argv[1][i];
            n++;
        }
    }
    new[n]='\0';
    printf("%s\n",new);
    write(1,new,strlen(new)+1);
    return 0;
}