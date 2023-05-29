// scrivere un programma che prende 2 righe di file di testo, ogni riga corrisponde a un comando con i rispettivi parametri, deve lanciare entrambi i comandi in modo che l'output del primo diventi input del secondo

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <execs.h>
int main(int argc, char *argv[])
{
    int pd[2];
    int pf[2];
    pipe(pd);
    pipe(pf);
    char *line = NULL;
    size_t len = 0;

    char *line2 = NULL;
    size_t len2 = 0;
    getline(&line, &len, stdin);
    getline(&line2, &len2, stdin);

    pid_t pid;
    
    pid = fork();
    if(pid == 0){
        close(pd[0]);
        // dup2(pd[1], STDOUT_FILENO);
        // system_nosh(line);
        write(pd[1], "helloworld", strlen("helloworld"));
        _exit(0);
    }
    else{
        close(pd[1]);
        char f[1];
        int i = 0;
        int res;
        while((res = read(pd[0], f, 1)) > 0){
            printf("%c\n", f[0]);
            write(pf[0], f, 1);
        }
        // dup2(pd[1], STDIN_FILENO);
        // system_nosh(line2);
        _exit(0);
    }
    return 0;
}
