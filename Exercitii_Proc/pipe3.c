#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char** argv){
    int p2c[2],x=1,v[101],n=0;
    pipe(p2c);

    
    int pid=fork();

    if (pid<0)
        printf("Error");
    
    if (pid==0){
        close(p2c[1]);
        while(1){
            if(read(p2c[0],&x,sizeof(int))<=0)
                break;
            if(read(p2c[0],&n,sizeof(int))<=0)
                break;
            if(read(p2c[0],&v,n*sizeof(int))<=0)
                break;
            if (x==0) break;
           
            for(int i=0;i<n-1;i++)
                for (int j=i+1;j<n;j++){
                    if (v[i]>v[j]){
                        int aux=v[i];
                        v[i]=v[j];
                        v[j]=aux;
                    }
                }
            for (int i=0;i<n;i++)
                printf("%d ",v[i]);
            printf("X: %d\n",x);
        }
        close(p2c[0]);
        exit(0);
    }
    close(p2c[0]);
    while(1){
       scanf("%d",&x);
        if (x==0) 
            break;
        else{
            v[n]=x;
            n++;
        }
        printf("A:");
        
        for (int i=0;i<n;i++)
            printf("%d ",v[i]);
        printf("X: %d, N:%d\n",x,n);
        write(p2c[1],&x,sizeof(int));
        write(p2c[1],&n,sizeof(int));
        write(p2c[1],&v,n*sizeof(int));
    }

    //for (int i=0;i<n;i++)
      // printf("%d ",v[i]);
    close(p2c[1]);
    wait(0);
    return 0;
}