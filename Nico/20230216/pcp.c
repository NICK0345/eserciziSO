// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Fare un programma di copia parallelo di file.
// pcp file1 file2
// pcp deve creare due processi figli; mentre un processo copia la prima meta’ del file, l'altro deve
// copiare l’altra meta’.

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define DEF 2


void copy(FILE * src, FILE *dest, unsigned int offset, unsigned int size){
    fseek(src, offset, 0);
    fseek(dest, offset, 0);
    char* buf = (char *)calloc(size, sizeof(char));
    int res = 0;
    if((res = fread(buf, sizeof(char), size, src)) > 0){
        fwrite(buf, sizeof(char), size, dest);
    }
    free(buf);
    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("File path not mentioned\n");
        exit(0);
    }

    int nProc = DEF;
    int tfnd = 0;
    int opt;
    while ((opt = getopt(argc, argv, "j:")) != -1) {
        switch (opt) {
        case 'j':
            nProc = atoi(optarg);
            tfnd = 1;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-j nProc]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    FILE *src = fopen(argv[tfnd? 3: 1], "r+");
    FILE *dest = fopen(argv[tfnd? 4: 2], "w");
    
    struct stat statbuf;
    int err = stat(argv[tfnd? 3: 1], &statbuf);
    if(err < 0){
        printf("\n\"%s \" could not open\n", argv[tfnd? 3: 1]);
        exit(2);
    }

    int offset = 0;
    int mid = statbuf.st_size/nProc;
    int st;
    for(int i = 0; i < nProc; i++){
        switch (fork()){
            case 0:
                if(i == nProc-1 && statbuf.st_size%nProc != 0) copy(src, dest, i*mid, mid+statbuf.st_size%nProc);
                else copy(src, dest, i*mid, mid);
                _exit(0);
            case -1:
                _exit(1);
        }
    }

    for(int i = 0; i < nProc; i++){
        wait(&st);
    }
    fclose(src);
    fclose(dest);
    return 0;
}