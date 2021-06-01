#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv){
    int p[argc][2];
    for (int i=1;i<argc;i++){
        pipe(p[i]);
        int pid=fork();
        if (pid==0){
            close(p[i][0]);
            dup2(p[i][1],1);
            execl("./prog1","./prog1",argv[i],NULL);
            close(p[i][1]);
            exit(1);
        }
        else{
            printf("Parent launched child: %d ->%s\n",pid,argv[i]);
        }
        close(p[i][1]);
    }
    for (int i=1;i<argc;i++){
        wait(0);
    }
    for (int i=1;i<argc;i++){
        int pid=fork();
        if (pid==0){
            char modif[100];
            read(p[i][0],modif,strlen(argv[i])+1);
            close(p[i][0]);
            execl("./prog2","./prog2",modif,NULL);
            exit(1);
        }
        else{
            close(p[i][0]);
        }
    }
    for (int i=1;i<argc;i++){
        wait(0);
    }
    return 0;
}