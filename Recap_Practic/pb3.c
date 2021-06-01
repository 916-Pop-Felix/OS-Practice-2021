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
    int a2p[2],b2p[2];
    srand(time(NULL));
    pipe(a2p);
    pipe(b2p);
    int pa=fork();
    if (pa==-1){
        printf("bad fork");
        exit(1);
    }
    if (pa==0){
        srand(time(NULL)^ getpid());
        int a[10]={0};
        close(a2p[0]);
        for (int i=0;i<10;i++){
            int x=rand()%(999-100+1)+100;
            while(x!=0){
                a[x%10]++;
                x/=10;
            }
        }
        write(a2p[1],&a,10*sizeof(int));
        close(a2p[1]);
        exit(0);
    }
    else
    {
        srand(time(NULL)^ getpid());
        int b[10]={0};
        int pb=fork();
        if (pb==-1){
            printf("bad fork");
            exit(1);
        }
        if (pb==0){
            close(b2p[0]);
            for (int i=0;i<10;i++){
                int x=rand()%(999-100+1)+100;
                while(x!=0){
                    b[x%10]++;
                    x/=10;
                }
            }
            write(b2p[1],&b,10*sizeof(int));
            close(b2p[1]);
            exit(0);
        }
    }
    wait(0);wait(0);
    int fa[10],fb[10];
    read(a2p[0],&fa,10*sizeof(int));
    read(b2p[0],&fb,10*sizeof(int));
    close(a2p[0]);
    close(b2p[0]);
    printf("The frequencies for A are: ");
    for (int i=0;i<10;i++){
        printf("%d ",fa[i]);
    }
    printf("\n");
    printf("The frequencies for B are: ");
    for (int i=0;i<10;i++){
        printf("%d ",fb[i]);
    }
    printf("\n");
    printf("Let's see who wins!\n");
    for (int i=0;i<10;i++){
        printf("%d - ",i);
        if (fa[i]>fb[i]){
            printf("Child A\n");
        }else{
            if (fa[i]<fb[i]){
                printf("Child B\n");
            }else{
                 printf("Draw\n");
            }
        }
    }
    printf("\n");
    return 0;
}