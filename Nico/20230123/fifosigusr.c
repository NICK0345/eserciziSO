#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void termination_handler (int signum){
    printf("ho ricevuto %d\n", signum);
}

int main (void){
    struct sigaction act;
    act.sa_handler = termination_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    printf("pid: %u\n", getpid());
    while(1)
        sleep(20);
    return 0;
}