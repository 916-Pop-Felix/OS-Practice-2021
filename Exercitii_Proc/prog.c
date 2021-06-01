#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int prime(int x){
    if (x<2){
        return 0;
    }
    if (x%2==0 && x!=2){
        return 0;
    }
    for (int d=3;d*d<=x;d+=2){
        if (x%d==0){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv){
    int i=atoi(argv[1]);
    if (i==0){
        int len=strlen(argv[1]);
        write(1,&len,sizeof(int));
    }
    else{
        if (prime(i)){
            write(1,&i,sizeof(int));
        }
        else{
            int zero=0;
            write(1,&zero,sizeof(int));
        }
    }
    return 0;
}