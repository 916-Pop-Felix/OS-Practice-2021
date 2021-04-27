#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc,char** argv){
    //execlp("ls","ls","-l",NULL);
    int pid;
    if (argc!=0){
        for (int i=0;i<argc;i++){
            pid=fork();
            if (pid==0){
                execl("./test.sh","./test.sh",argv[i],NULL);
                printf("Error");
                exit(1);
            }
        }
        for (int i=0;i<argc;i++){
            wait(0);
        }
    }
    return 0;
}