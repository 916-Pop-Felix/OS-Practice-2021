#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
//Write a C program that creates two processes A and B that communicate using pipes. 
//Process A sends to process
// B two strings (words). Process B receives two strings and checks if they have the same length or length 
//difference of one. If they do, B sends to A an “ok” message and the game ends. If they do not, B sends to A 
//the “notok” message and A will add a random digit at the beginning of the shortest string and remove the last
//letter of the longest string, then send the two modified strings to B. B performs the checks and so on until 
//the two strings have a difference in length <=1.

void modify_chars(char a[],char b[]){
    char newa[100],newb[100];
    if (strlen(a)<strlen(b)){
        for (int i=0;i<strlen(a);i++){
            newa[i]=a[i];
        }
        newa[strlen(a)]=rand()%10+'0';
        newa[strlen(a)+1]='\0';
        for (int i=0;i<strlen(b)-1;i++){
            newb[i]=b[i];
        }
        newb[strlen(b)-1]='\0';
    }
    else{
        for (int i=0;i<strlen(b);i++){
            newb[i]=b[i];
        }
        newb[strlen(b)]=rand()%10+'0';
        newb[strlen(b)+1]='\0';
        for (int i=0;i<strlen(a)-1;i++){
            newa[i]=a[i];
        }
        newa[strlen(a)-1]='\0';
    }
    strcpy(a,newa);
    strcpy(b,newb);
}
char notok[]={"notok"};
char ok[]={"ok"};
int main(int argc, char** argv){
    int a2b[2],b2a[2];
    int pa,pb; 
    char which_ok[8];
    char a[100],b[100];
    pipe(a2b);
    pipe(b2a);
   
    srand(time(NULL));
   
    pa=fork();
    if (pa<0){
            printf("Bad fork");
            exit(1);
    }
    if (pa==0){
        close(a2b[0]);
        close(b2a[1]);
         scanf("%s",a);
        scanf("%s",b);
        printf("A: %s , B: %s \n",a,b);
        write(a2b[1],&a,sizeof(a));
        write(a2b[1],&b,sizeof(b));
        while(1){
            if (read(b2a[0],&which_ok,sizeof(which_ok))<=0){
                break;
            }
            if (strcmp(which_ok,ok)==0){
                break;
            }
            modify_chars(a,b);
            printf("A: %s , B: %s \n",a,b);
            write(a2b[1],&a,sizeof(a));
            write(a2b[1],&b,sizeof(b));
        }
        close(b2a[0]);
        close(a2b[1]);
        exit(0);
    }
    else{
        pb=fork();
        if (pb<0){
            printf("Bad fork");
            exit(1);
        }
        if (pb==0){
            close(a2b[1]);close(b2a[0]);
            while(1){
                if(read(a2b[0],&a,sizeof(a))<=0){
                    break;
                }
                 if(read(a2b[0],&b,sizeof(b))<=0){
                    break;
                }
                if (abs(strlen(a)-strlen(b))<=1)
                    strcpy(which_ok,ok);
                else{
                    strcpy(which_ok,notok);
                }
                write(b2a[1],&which_ok,sizeof(which_ok));
            }
            close(a2b[0]);
            close(b2a[1]);
            exit(0);
        }
    }
    wait(0);
    wait(0);
    return 0;
}