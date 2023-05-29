// scrivere due programmi C, tx e rx:
// tx trasferisce a rx stringhe di max 8 caratteri usando i valori assegatu ai segnali(usando i valori della sigqueue).
// il programma rx deve per prima cosa stampare il proprio pid e attendere segnali
// il programma tx ha due parametri, il pid di rx e il messaggio.
// es. tx 22255 sigmsg, sia rx il processo con pid 22255, rx deve stampare sigmsg

// NAME
//        sigqueue - queue a signal and data to a process

// SYNOPSIS
//        #include <signal.h>

//        int sigqueue(pid_t pid, int sig, const union sigval value);

//    Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

//        sigqueue(): _POSIX_C_SOURCE >= 199309L

// DESCRIPTION
//        sigqueue()  sends  the signal specified in sig to the process whose PID
//        is given in pid.  The permissions required to send  a  signal  are  the
//        same  as for kill(2).  As with kill(2), the null signal (0) can be used
//        to check if a process with a given PID exists.

//        The value argument is used to specify an accompanying item of data (ei‐
//        ther an integer or a pointer value) to be sent with the signal, and has
//        the following type:

//            union sigval {
//                int   sival_int;
//                void *sival_ptr;
//            };

//        If the receiving process has installed a handler for this signal  using
//        the  SA_SIGINFO  flag to sigaction(2), then it can obtain this data via
//        the si_value field of the siginfo_t structure passed as the second  ar‐
//        gument  to  the handler.  Furthermore, the si_code field of that struc‐
//        ture will be set to SI_QUEUE.

// RETURN VALUE
//        On success, sigqueue() returns 0, indicating that the signal  was  suc‐
//        cessfully  queued  to the receiving process.  Otherwise, -1 is returned
//        and errno is set to indicate the error.

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b){
    return (a<b? a: b);
}

void * strtoptr(char *word, int *pos){
    int i, len;
    len = min(strlen(word+(*pos)*sizeof(char)), 8);
    char *buf = (char*) calloc(len*2+1, sizeof(char));
    for(i = 0; i<len; i++){
        sprintf(buf+(i)*2, "%02x", word[i+*pos]);
    }
    (*pos) = (*pos)+len;
    return (void *)strtol(buf, NULL, 16);
}

int main(int argc, char *argv[])
{
    int sig = 0;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigprocmask (SIG_BLOCK, &mask, NULL);
        union sigval value;
    sigqueue(info->si_pid, SIGUSR2, value);
    union sigval value;
    int pid = atoi(argv[1]);
    int pos = 0;
    while(strlen(argv[2]+pos) > 0){
        value.sival_ptr = strtoptr(argv[2], &pos);
        if(sigqueue(pid, SIGUSR2, value) != 0) {
            perror("SIGSENT-ERROR:");
        }
        sigwait(&mask, &sig);
    }
    value.sival_ptr = NULL;
    if(sigqueue(pid, SIGUSR1, value) == 0) {
        printf("signal sent successfully!!\n");
    } else {
        perror("SIGSENT-ERROR:");
    }

    return 0;
}
