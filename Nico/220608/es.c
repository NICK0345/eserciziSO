// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Scrivere il programma invsymlink che prende come parametro il pathname di un file.
// Se il parametro è un link simbolico il programma inverte il link simbolico: il file puntato viene messo al
// posto del file link simbolico e nella precedente collocazione dove era il file puntato dal link simbolico
// viene messo un link simbolico che punti alla nuova collocazione del file. (*)
// Se A e B indicano lo stesso file perché B è un link simbolico che punta ad A, allora "invsymlink B" deve
// fare in modo che B diventi il file che precedentemente era A e A diventi un link simbolico che punti a
// B.
// (*) usare il pathname completo che può essere calcolato con realpath(3).

// unsigned char d_type

// DT_UNKNOWN 
// The type is unknown. Only some filesystems have full support to return the type of the file, others might always return this value.

// DT_REG
// A regular file.

// DT_DIR
// A directory.

// DT_FIFO
// A named pipe, or FIFO. See FIFO Special Files.

// DT_SOCK
// A local-domain socket.

// DT_CHR
// A character device.

// DT_BLK
// A block device.

// DT_LNK
// A symbolic link.


#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
void invert(char *slink){
    char real[100];
    if(realpath(slink, real) == NULL){
        perror("realpath");
        exit(1);
    }
    unlink(slink);
    FILE *A = fopen(real, "r");
    FILE *B = fopen(slink, "w+");
    char c = fgetc(A);
    while (c != EOF)
    {
        fputc(c, B);
        c = fgetc(A);
    }
    fclose(A);
    fclose(B);
    unlink(real);
    symlink(slink, real);
}

int main(int argc, char *argv[]){
    if(argc < 2){
        exit(1);
    }
    struct stat sb;
    if(lstat(argv[1], &sb) == -1){
        perror("lstat");
        exit(1);
    }
    if((sb.st_mode & S_IFMT) == S_IFLNK){
        invert(argv[1]);
        return 0;
    }
    else if((sb.st_mode & S_IFMT) == S_IFDIR){
        DIR *dir;
        struct dirent *entry;
        if ((dir = opendir(argv[1])) == NULL) perror("opendir() error");
        else{
            // opendir genera un'immagine momentanea di quando apri la directory, readdir legge quell'immagine, ricalcolo lstat(), allora viene ritornato il tipo aggiornato del file, creando effetti indesiderati
            while(entry = readdir(dir)){
                // struct stat f;
                // if(lstat(entry->d_name, &f) == -1){
                //     perror("lstat");
                //     exit(1);
                // }
                // if((f.st_mode & S_IFMT) == S_IFLNK){
                char path[100];
                char buf[100];
                char real[100];
                if(entry->d_type == DT_LNK){
                    printf("%s ", entry->d_name);
                    realpath(entry->d_name, real);
                    printf("%s ", real);
                    readlink(entry->d_name, path, 100);
                    realpath(path, buf);
                    printf("%s %s\n", path, buf);
                    //invert(entry->d_name);
                }
            }
        }
    }

    return 0;
}