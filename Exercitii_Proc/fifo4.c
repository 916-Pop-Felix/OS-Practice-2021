#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#define MIN 999999
#define MAX -999999

/*
1. Write a C program that will read from keyboard an array of N numbers and it will generate 3 child processes. 
The main process will send to each of the child processes the array which will do the following:
    - c1: compute maximum 
    - c2: compute minimum 
    - c3: compute average 
The results of the child processes will be returned to the part that will display them on the screen. 
*/
int main(int argc, char** argv){
    mkfifo("fp2a",0666);
    mkfifo("fa2p",0666);
    mkfifo("fp2b",0666);
    mkfifo("fb2p",0666);
    int fp2a,fa2p,fp2b,fb2p;
    int n,v[101];
    int fa;
   
    fa=fork();
    if (fa<0){
        printf("Error");
        exit(1);
    }
    if (fa==0){
        int minn=MIN;
        fp2a=open("fp2a",O_RDONLY);
        read(fp2a,&n,sizeof(int));
        read(fp2a,&v,n*sizeof(int));
        close(fp2a);
        for (int i=0;i<n;i++){
            if (v[i]<minn){
                minn=v[i];
            }
        }
        fa2p=open("fa2p",O_WRONLY);
        write(fa2p,&minn,sizeof(int));
        close(fa2p);
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
            fp2b=open("fp2b",O_RDONLY);
            read(fp2b,&n,sizeof(int));
            read(fp2b,&v,n*sizeof(int));
            close(fp2b);
            int s=0;
            for (int i=0;i<n;i++){
                s+=v[i];
            }
            int res=s/n;
            fb2p=open("fb2p",O_WRONLY);
            write(fb2p,&res,sizeof(int));
            close(fb2p);
            exit(0);
        }
    }
   
    printf("Enter the number of values: ");
    scanf("%d",&n);
    printf("Enter the values: ");
    for (int i=0;i<n;i++){
        scanf("%d",&v[i]);
    }
    fp2a=open("fp2a",O_WRONLY);
    write(fp2a,&n,sizeof(int));
    write(fp2a,&v,n*sizeof(int));
    close(fp2a);
    fp2b=open("fp2b",O_WRONLY);
    write(fp2b,&n,sizeof(int));
    write(fp2b,&v,n*sizeof(int));
    close(fp2b);

    int minn,s;
    fa2p=open("fa2p",O_RDONLY);
    fb2p=open("fb2p",O_RDONLY);

    read(fa2p,&minn,sizeof(int));
    read(fb2p,&s,sizeof(int));
    close(fa2p);
    close(fb2p);

    printf("The min in the vector is %d\n",minn);
    printf("The avg in the vector is %d\n",s);
    wait(0);wait(0);
    unlink("fp2a");
    unlink("fa2p");
    unlink("fp2b");
    unlink("fb2p");
    
    return 0;
}