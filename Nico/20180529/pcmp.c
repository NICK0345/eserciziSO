// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Fare un programma di confronto parallelo di file.
// pcmp file1 file2
// non stampa nulla se i due file sono uguali altrimenti stampa "file1 file2 differ". pcmp deve creare due processi figli;
// mentre un processo controlia la prima meta’ del file, l'altro deve controllare l’altra meta’.
// Se un dei due processi figli trova una differenza, termina immediatamente segnalandolo al padre con opportuno
// valore di ritorno. In questo caso il padre deve terminare l'altro processo

#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdint.h>
pid_t pid[2];
int wstatus[2];


int main(int argc, char *argv[]){
    unsigned char *f;
    int size;
    struct stat s;
    const char * file_name = argv[1];
    int fd = open (argv[1], O_RDONLY);

    /* Get the size of the file. */
    int status = fstat (fd, & s);
    size = s.st_size;

    unsigned char *f2;
    int size2;
    struct stat s2;
    const char * file_name2 = argv[2];
    int fd2 = open (argv[2], O_RDONLY);

    /* Get the size of the file. */
    fstat (fd2, & s2);
    size2 = s2.st_size;

    if(size != size2){
        printf("file diversi\n");
        exit(0);
    }
    int middle = size/2;

    f = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    f2 = (char *) mmap (0, size2, PROT_READ, MAP_PRIVATE, fd2, 0);

    int children = 2;
    int initial = 0;
    for(int i = 0; i < children; i++){
        pid_t p = fork();
        switch (p){
            case 0:
                for(int j = initial; j < initial+middle; j++){
                    printf("%c %c\n", f[j], f2[j]);
                    if(f[j] != f2[j]){
                        printf("file diverso\n");
                        _exit(100);
                    }
                }
                _exit(1);
                break;
            case -1:
                perror("fork");
                _exit(EXIT_FAILURE);
            default:
                pid[i] = p;
                initial+=middle;
                break;
        }
    }
    int w;
    for(int i = 0; i < 2; i++){
        pid_t p = wait(&w);
        if(WIFEXITED(status)){
            printf("%d\n", WEXITSTATUS(w));
            fflush(stdout);
            if(WEXITSTATUS(w) == 100){
                for(int j = 0; j < children; j++){
                    if(p != pid[j]){
                        printf("%d", pid[j]);
                        kill(pid[j], SIGTERM);
                        waitpid(pid[j], &w, 0);
                    }
                }
                break;
            }
        }
    }
    
    printf("file uguali\n");
    return 0;
}
