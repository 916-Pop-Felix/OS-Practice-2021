#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

//4. Write a program that creates a child process. The two communicate through a pipe.
// The parent reads a string with >25 characters and sends it to the child,
 //which removes 1 vowel and sends it to the parent, which removes the first and the last character 
 //and sends it to the child back which removes again a vowel and sends it back 
 //.... and so on untill the string contains 3 or less characters.

void delete_vowel(char a[]){
    int k=0,nb=0;
    char b[26];
    for (int i=0;i<strlen(a);i++){
        if (strchr("AEIOUaeiou",a[i])){
            k++;
            if (k!=1){
                b[nb]=a[i];
                nb++;
            }
        }
        else{
            b[nb]=a[i];
            nb++;
        }
    }
    b[nb]='\0';
    strcpy(a,b);
}
void remove_first_last(char a[]){
    int nb=0;
    char b[26];
    for (int i=1;i<strlen(a)-1;i++){
        b[nb]=a[i];
        nb++;
    }
     b[nb]='\0';
    strcpy(a,b);
}

int main(int argc, char** argv){
    int a2b[2],b2a[2];
    pipe(a2b);
    pipe(b2a);
    int pa,pb;
    char a[26];
    pa=fork();
    if (pa<0){
        printf("Error");
        exit(1);
    }
    if (pa==0){
        close (a2b[0]);
        printf("Enter the char: ");
        scanf("%s",&a); 
        write(b2a[1],a,sizeof(a));
        close(b2a[1]);
        while(1){
            if(read(b2a[0],&a,sizeof(a))<0)
                break;
            if (strlen(a)<=3)  
                break;
            printf("A: %s ->",a);
            delete_vowel(a);
            printf("A: %s \n",a);
            write(a2b[1],&a,sizeof(a));
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
                if (read(a2b[0],&a,sizeof(a))<0) 
                    break;
                if (strlen(a)<=3) break;
                printf("B: %s ->",a);
                remove_first_last(a);
                printf("B: %s \n",a);
                write(b2a[1],&a,sizeof(a));
            }
            close(b2a[1]);
            close (a2b[0]);
            exit(0);
        }
    }
    wait(0);wait(0);
    return 0;
}