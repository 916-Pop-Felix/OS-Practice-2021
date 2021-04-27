#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char** argv){
    mkfifo("fa2b",0666);
    mkfifo("fb2a",0666);
    int fa2b,fb2a;
    int fa;
   
    fa=fork();
    if (fa<0){
        printf("Error");
        exit(1);
    }
    if (fa==0){
        int x1,x2;
        scanf("%d",&x1);
        scanf("%d",&x2);
        fa2b=open("fa2b",O_WRONLY);
        write(fa2b,&x1,sizeof(int));
        write(fa2b,&x2,sizeof(int));
        close(fa2b);
        fb2a=open("fb2a",O_RDONLY);
        int res;
        read(fb2a,&res,sizeof(int));

        printf("The random number is %d",res);
        close(fb2a);
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
            int x,xx;
            fa2b=open("fa2b",O_RDONLY);
            read(fa2b,&x,sizeof(int));
            read(fa2b,&xx,sizeof(int));
            close(fa2b);
            
            fb2a=open("fb2a",O_WRONLY);
            if (x>xx){
                int aux=x;
                x=xx;
                xx=aux;
            }
            srand(time(0));
            int r=rand()%xx+x;
            //while(!(r>x && r<xx)){
            //    r=rand();
           // }
            write(fb2a,&r,sizeof(int));
            close(fb2a);
            exit(0);
        }
    }
   
    wait(0);wait(0);
    unlink("fa2b");
    unlink("fb2a");
    return 0;
}