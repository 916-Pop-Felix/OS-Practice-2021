#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
//NU MERE
int main(int argc, char** argv){
    mkfifo("fa2b",0666);
    int fa2b;
    int fa;
   
    fa=fork();
    if (fa<0){
        printf("Error");
        exit(1);
    }
    if (fa==0){
        int n,v[100];
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d ",&v[i]);
        } 
        printf("%d ",n);
        for(int i=0;i<n;i++){
            printf("%d ",v[i]);
        } 
        fa2b=open("fa2b",O_WRONLY);
        write(fa2b,&n,sizeof(int));
        write(fa2b,&v,n*sizeof(int));
        close(fa2b);
        exit(0);
    }
    else{
        int fb;
        fb=fork();
        if (fb<0){
            printf("Error");
            exit(1);
        }
        if (fb==0){
            int pa=fork();
            int pa2b[2];pipe(pa2b);
            if (pa==0){
                int n,v[100];
                int s=0;
                close(pa2b[0]);
                fa2b=open("fa2b",O_RDONLY);
                read(fa2b,&n,sizeof(int));
                read(fa2b,&v,n*sizeof(int));
                 printf("%d ",n);
        for(int i=0;i<n;i++){
            printf("%d ",v[i]);
        } 
                close(fa2b);
                for (int i=0;i<n;i++){
                    s+=v[i];
                }
                write(pa2b[1],&s,sizeof(int));
                close(pa2b[1]);
                exit(0);
            }
            else{
                int pb=fork();
                if (pb==0){
                    int s=0;
                    close(pa2b[1]);
                    read(pa2b[0],&s,sizeof(int));
                    close(pa2b[0]);
                    printf("The final sum of the array is %d\n",s);
                    exit(0);
                }
            }
            wait(0);wait(0);
            close(fa2b);
            exit(0);
        }
    }
   
    wait(0);wait(0);
    unlink("fa2b");
    return 0;
}