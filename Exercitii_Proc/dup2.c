#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// 11. Wrie a program that receives as command line arguments any number of strings. For each argument, 
// it creates a new process that launches a C or Shell program that checks if the argument is a prime number,
//  then it returns that number as int, if it's a number not prome it returns zero, if it's a string it 
//  returns the length of the string, sending these numbers to the main program using a pipe. The main
//   program receives these numbers, prints them and computes they sum.

int main(int argc, char** argv){
    int p[argc][2];
    int s=0;
    for (int i=1;i<argc;i++){
        pipe(p[i]);
        int pid=fork();
        if (pid==0){
            close(p[i][0]);
            dup2(p[i][1],1);
            execl("./prog","./prog",argv[i],NULL);
            close(p[i][1]);
            exit(1);
        }
        else{
            printf("Parent launched child: %d ->%s\n",pid,argv[i]);
        }
    }
    for (int i=1;i<argc;i++){
        close(p[i][1]);
        int nr=0;
        read(p[i][0],&nr,sizeof(int));
        printf("Main recieved %d\n",nr);
        s+=nr;
        close(p[i][0]);
    }
    for (int i=1;i<argc;i++){
        wait(0);
    }
    printf("Sum is %d\n",s);
    return 0;
}