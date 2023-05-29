#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

FILE *fd;
char *name; 

void termination_handler(int signum){
    fclose(fd);
    unlink(name);
    _exit(0);
}

int main(int argc, char *argv[]){
    //creo la fifo
    mkfifo(argv[1], 0666);

    fd = fopen(argv[1], "r");
    name = argv[1];
    unsigned long pid;
    unsigned sig;
    struct sigaction act;
    act.sa_handler = termination_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &act, NULL);
    while(1){
        fscanf(fd, "%lu %u\n", &pid, &sig);
        kill(pid, sig);
        fd = fopen(argv[1], "r");
    }
    return 0;
}