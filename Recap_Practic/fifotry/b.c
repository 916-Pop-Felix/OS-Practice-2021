#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv){
    int a2b, b2a, n;
//    a2b = mkfifo("a2b", O_RDONLY);
  //  b2a = mkfifo("b2a", O_WRONLY);
    a2b = open("a2b", O_RDONLY);
    b2a = open("b2a", O_WRONLY);
    //a2b = open("a2b", O_WRONLY);

//    n=20;
  //  write(a2b, &n, sizeof(int));
    while(1){
        if(read(a2b, &n, sizeof(int))<=0){
            break;
        }
        if(n<=0){
            break;
        }
        printf("B: %d -> %d\n", n, n-1);
        n--;
        write(b2a, &n, sizeof(int));
    }
    close(a2b);
    close(b2a);
//    unlink("a2b");
  //  unlink("b2a");
    return 0;
}