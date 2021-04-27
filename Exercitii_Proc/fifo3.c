#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

/*
Using PIPE channels create and implement the following scenario: 
Process A reads N integer numbers from the keyboard and sends them another process named B. 
Process B will add a random number, between 2 and 5, to each received number from 
process A and will send them to another process named C. 
The process C will add all the received numbers and will send the result back to process A. 
All processes will print a debug message before sending and after receiving a number.
*/

int main(int argc, char** argv){
    mkfifo("fa2b",0666);
    mkfifo("fb2c",0666);
    mkfifo("fc2a",0666);
    int fa2b,fb2c,fc2a;
    int fa;
    int n,v[101],s=0;
    fa=fork();
    if (fa<0){
        printf("Error");
        exit(1);
    }
    if (fa==0){
        printf("Enter the number of values: ");
        scanf("%d",&n);
        printf("Enter the values: ");
        for (int i=0;i<n;i++){
            scanf("%d",&v[i]);
        }
        fa2b=open("fa2b",O_WRONLY);
        write(fa2b,&n,sizeof(int));
        write(fa2b,&v,n*sizeof(int));
        close(fa2b);
        fc2a=open("fc2a",O_RDONLY);
        read(fc2a,&s,sizeof(int));
        close(fc2a);
        printf("The final sum is %d",s);
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
            fa2b=open("fa2b",O_RDONLY);
            read(fa2b,&n,sizeof(int));
            read(fa2b,&v,n*sizeof(int));
            close(fa2b);
            printf("\nB: ");
            for (int i=0;i<n;i++)
                printf("%d ",v[i]);
            for (int i=0;i<n;i++){
                v[i]+=rand()%5+2;
            }
            fb2c=open("fb2c",O_WRONLY);
            write(fb2c,&n,sizeof(int));
            write(fb2c,&v,n*sizeof(int));
            close(fb2c);
            exit(0);
        }
        else{
            int fc;
            fc=fork();
            if (fc<0){
                printf("Error");
                exit(1);
            }
            if (fc==0){
                fb2c=open("fb2c",O_RDONLY);
                read(fb2c,&n,sizeof(int));
                read(fb2c,&v,n*sizeof(int));
                close(fb2c);
                printf("\nC: ");
                for (int i=0;i<n;i++)
                    printf("%d ",v[i]);
                for (int i=0;i<n;i++){
                    s+=v[i];
                }
                
                fc2a=open("fc2a",O_WRONLY);
                write(fc2a,&s,sizeof(int));
                close(fc2a);
                exit(0);
            }
        }
    }
    
    wait(0);wait(0);wait(0);
    unlink("fa2b");
    unlink("fb2c");
    unlink("fc2a");
    return 0;
}