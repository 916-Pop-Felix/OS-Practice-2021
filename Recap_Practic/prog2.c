#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    int len=strlen(argv[1]);
    printf("Resulted %s of str count %d\n",argv[1],len);
    return 0;
}