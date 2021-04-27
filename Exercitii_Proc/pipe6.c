#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

//4. Write a C program that will read from keyboard N numbers, for each number 
//it will generate a child process to whom it will send the number. 
//The child process will check if the number is a prime number and it will 
//return a response to the parent that will display it on the screen. 


int is_prime(int x){
    if (x<2){
        return 0;
    }
    if (x%2==0 && x!=2){
        return 0;
    }
    for (int d=3;d*d<=x;d+=2){
        if (x%d==0)
            return 0;
    }
    return 1;
}

int main(int argc, char** argv){
    int v[101],n;
    printf("Enter how many number you will input: ");
    scanf("%d",&n);
    printf("Enter the numbers: ");
    for (int i=0;i<n;i++)
        scanf("%d",&v[i]);
    
    for (int i=0;i<n;i++){
        int pc,p2c[2],c2p[2],ok;
        pipe(p2c);
        pipe(c2p);
        pc=fork();
        if (pc<0){
            printf("Error");
            exit(1);
        }
        if (pc==0){
            close(p2c[1]);
            close(c2p[0]);
            read(p2c[0],&v[i],sizeof(int));
            ok=is_prime(v[i]);
            write(c2p[1],&ok,sizeof(int));
            close(p2c[0]);
            close(c2p[1]);
            exit(0);
        }
        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1],&v[i],sizeof(int));

        read(c2p[0],&ok,sizeof(int));
        if (ok)
            printf("%d is prime\n",v[i]);
        else
            printf("%d is not prime\n",v[i]);

        close(p2c[1]);
        close(c2p[0]);
    }
    for (int i=0;i<n;i++)
        wait(0);
    return 0;
}