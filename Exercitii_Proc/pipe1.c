#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

//X MERGE
int main(int argc, char** argv){
    int a2b[2],b2a[2],n;
    pipe(a2b);
    pipe(b2a);
    int pa,pb;
    pa=fork();
    if (pa<0){
        printf("Error");
        exit(1);
    }
    if (pa==0){
        int x;
        //close(b2a[1]);
        close (a2b[0]);
        printf("Enter the number: ");
        scanf("%d",&x); 
        n=x;
        write(b2a[1],&n,sizeof(int));
        close(b2a[1]);
      
        while(1){
            read(b2a[0],&n,sizeof(int));
            printf("A: %d -> %d\n",n,n-4);
            if (n<10)  break;
            
            //n--;
            n-=4;
            write(a2b[1],&n,sizeof(int));
        }
        close(a2b[1]);close(b2a[0]);
        exit(0);
    }
    else{
        pb=fork();
        if (pb<0){
            printf("error");
            exit(1);
        }
        if (pb==0){
            close(a2b[1]);close(b2a[0]);
            while(1){
                read(a2b[0],&n,sizeof(int));
                printf("B: %d -> %d\n",n,n-1);
                if (n<10) break;
                
                n--;
                write(b2a[1],&n,sizeof(int));
            }
            close(b2a[1]);
            close (a2b[0]);
            exit(0);
        }
    }
    wait(0);wait(0);
    return 0;
}