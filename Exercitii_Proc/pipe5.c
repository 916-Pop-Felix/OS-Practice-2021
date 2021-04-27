#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

//3. Write a C program that will read from keyboard a string of characters, will generate a child process and to whom it will send the input.
// The child process will sort all the charcters alphabetically and it will return the results to the parent 

void sort_alphabetically(char a[]){
    for (int i=0;i<strlen(a)-1;i++){
        for (int j=i+1;j<strlen(a);j++){
            //char *x,*y;
            //x=tolower(a[i]);
            //y=tolower(a[j]);
            if (a[i]>a[j]){
                char aux=a[i];
                a[i]=a[j];
                a[j]=aux;
            }
        }
    }
}

int main(int argc, char** argv){
    int p2c[2],c2p[2],pc;
    char a[30];
    pipe(p2c);
    pipe(c2p);
    pc=fork();
    if (pc==0){
        close(p2c[1]);
        close(c2p[0]);
        read(p2c[0],&a,sizeof(a));
        sort_alphabetically(a);
        write(c2p[1],&a,sizeof(a));
        close(p2c[0]);
        close(c2p[1]);
        exit(0);

    }
    if (pc<0){
        printf("Error");
        exit(1);
    }
    close(p2c[0]);
    close(c2p[1]);
    printf("Enter the char: ");
    scanf("%s",&a);
    printf("%s -> ",a);
    write(p2c[1],&a,sizeof(a));
    read(c2p[0],&a,sizeof(a));
    printf("%s\n",a);
    close(p2c[1]);
    close(c2p[0]);
    wait(0);
    return 0;
}