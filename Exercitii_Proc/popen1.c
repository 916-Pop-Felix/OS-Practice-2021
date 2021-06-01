#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
//Scrieti un program in C care preia ca argumente din linia de comanda 
//nume de fisiere, si executa un script shell care determina cuvantul cel
//mai des intalnit in acel fisier. Programul primeste inapoi cuvantul si il afiseaza
//in consola in programul C impreuna cu fisierul de care apartine.

int main(int argc, char* argv[]){
    for (int i=1;i<argc;i++){
        char* a=(char*)malloc(100*sizeof(char));
        FILE* fp;
        char* execs=(char*)malloc(150*sizeof(char));
        
        strcat(execs,"awk '{ if (++words[$0] > max) { max = words[$0]; maxW=$0 } } END { print maxW }' ");
        strcat(execs,argv[i]);
        fp = popen(execs,"r");
        fscanf(fp,"%s",a);
        printf("%s is the most common word in %s\n",a,argv[i]);
        pclose(fp);
        free(a);
        free(execs);
    }
    return 0;
}