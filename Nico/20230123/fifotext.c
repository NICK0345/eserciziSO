// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Scrivere un programma fifotext che:
// * crei una named pipe (FIFO) al pathname indicato come primo (e unico) argomento.
// * apra la named pipe in lettura
// * stampi ogni riga di testo ricevuta
// * se la named pipe viene chiusa la riapra
// * se riceve la riga "FINE" termini cancellando la named pipe.
// Esempio:
// fifotext /tmp/ff
// ....
// se in un altra shell si fornisce il comando: "echo ciao > /tmp/ff", fifotext stampa ciao e rimane in attesa
// (questo esperimento si può provare più volte). Con il comando "echo FINE > /tmp/ff" fifotext termina.
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int fd;
    //creo la fifo
    mkfifo(argv[1], 0666);

    fd = open(argv[1], O_RDONLY);

    char c[6];
    int reopen = 1;
    int first = 1;
    int num = 0;
    while(1){
        while(1){
            if((num = read(fd, c, sizeof(c))) <= 0) break;
            write(STDIN_FILENO, c, num);
            if(strncmp(c, "FINE\n", num) == 0 && first) reopen = 0;
            first = 0;
            memset(c, sizeof(c), 0);
        }
        if(reopen) {
            fd = open(argv[1], O_RDONLY);
            first = 1;
            memset(c, sizeof(c), 0);
            num = 0;
        }
        else break;
    }
    close(fd);
    unlink(argv[1]);
    return 0;
}