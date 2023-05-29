// Dato un estratto di un file di log come questo:
// Sep 20 19:58:32 eipi ntpd[2051]: Listen normally on 99 eth0 [fe80::8456:a70]:123
// Scrivere un programma che lo mostri alla stessa velocita' allla quale e' stato generato.
// In questo caso dovrebbe scrivere le prime dur righe, attendere 2 secondi, mostrare la terza, dopo un secondo la
// quarta quindi dopo una attesa di 13 secondi la quinta e la sesta dopo un ulteriore secondo.

#define _GNU_SOURCE
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(argc < 2) exit(EXIT_FAILURE);
    FILE *fp = fopen(argv[1], "r");
    char *line = NULL;
    time_t old;
    int count = 0;
    size_t len = 0;

    while(getline(&line, &len, fp) != -1) {
        struct tm tm;
        time_t t;
        old = t;
        strptime(line, "%b %d %H:%M:%S", &tm);
        tm.tm_isdst = -1;
        t = mktime(&tm);
        if(count == 0) old = t;
        switch (fork()) {
            case 0:
                printf("%s", line);
                _exit(0);
            case -1:
                perror("fork");
                _exit(1);
            default:
                printf("%ld", (long) t-old);
                sleep((int) t-old);
                count++;
                break;
        }
    }

    for(int i = 0; i < count; i++){
        wait(NULL);
    }

    free(line);
    exit(EXIT_SUCCESS);
}
