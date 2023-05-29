
// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Lo scopo di questo esercizio è di scrivere un programma che usando la system call signalfd quando riceve un
// segnale SIGUSR1 o SIGUSR2 scriva in un file della directory corrente con nume uguale al pid del processo che ha
// inviato il segnale, il tipo di segnale ricevuto e l'ora esatta di ricezione del segnale. (se il file non esiste deve essere
// creato).
// un esempio di file risultante potrebbe essere:
// $ cat 20231
// USR1 Fri Sep 21 10:40:56 CEST 2018
// USR1 Fri Sep 21 10:40:58 CEST 2018
// USR2 Fri Sep 21 10:41:26 CEST 2018

#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]){
    sigset_t mask;
    int sfd;
    struct signalfd_siginfo fdsi;
    ssize_t s;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    /* Block signals so that they aren't handled
        according to their default dispositions */

    printf("my pid is %d\n", getpid());

    sigprocmask(SIG_BLOCK, &mask, NULL);

    sfd = signalfd(-1, &mask, 0);
    for (;;) {
        s = read(sfd, &fdsi, sizeof(fdsi));

        if (fdsi.ssi_signo == SIGUSR2 || fdsi.ssi_signo == SIGUSR1) {
            //crea un file con pid name, scrivere dentro il segnale e data
            char str[4096];
            snprintf(str, 4096, "%d", fdsi.ssi_pid);
            FILE *f = fopen(str, "a");
            
            char dest[70];                                                                
            int ch;                                                                       
            time_t temp;                                                                  
            struct tm *timeptr;   
            temp = time(NULL);                                                            
            timeptr = localtime(&temp);                                                   
            ch = strftime(dest,sizeof(dest)-1,"%a %b %d %OH:%OM:%OS %Z %EY", timeptr);                            
            fprintf(f, "%s %s\n", (fdsi.ssi_signo == SIGUSR2? "SIGUSR2": "SIGUSR1"), dest);
            fflush(f);
            fclose(f);
        }
    }
}
