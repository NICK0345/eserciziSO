// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Scrivere il programma nonest_symlink che ha come parametro il pathname di una directory.
// Il programma deve cercare tutti i link simbolici presenti nella directory e cancelli ogni link simbolico
// anidificato (link simbolico che punta a link simbolico).

// Esercizio 2: Linguaggio C: 10 punti
// Scrivere il programma nest2hard: che ha come parametro il pathname di una directory.
// Il programma deve cercare tutti i link simbolici presenti nella directory e sostituire ogni link simbolico
// nidificato (link simbolico che punta a link simbolico) con un link fisico del file puntato.

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
#include <string.h>
// hard link aumenta inode e vnode, se viene cancellato il file originale, con il hard link esso esiste ancora, mentre symlink non aumenta inode e vnode del file originale, quindi se viene cancellato il file originale, allora il symlink e' corrotto

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Argument");
        exit(1);
    }
    struct stat sb;
    if(lstat(argv[1], &sb) == -1){
        perror("lstat");
        exit(1);
    }
    if((sb.st_mode & S_IFMT) == S_IFDIR){
        DIR *dir;
        struct dirent *entry;
        char *fullpath, *interm, *fullinterm;
        if ((dir = opendir(argv[1])) == NULL) perror("opendir() error");
        while(entry = readdir(dir)){
            if(entry->d_type == DT_LNK){
                interm = calloc(1024, 1);
                fullinterm = calloc(1024, 1);
                fullpath = calloc(1024, 1);
                fullpath = strcat(strcat(strcat(fullpath, argv[1]), "/"), entry->d_name);
                readlink(fullpath, interm, sizeof(interm)-1);
                fullinterm = strcat(strcat(strcat(fullinterm, argv[1]), "/"), interm);
                lstat(fullinterm, &sb);
                printf("%s, %s\n", fullpath, fullinterm);
                //se e' un hard_link allora S_IFLNK
                if((sb.st_mode & S_IFMT) == S_IFLNK){
                    char *realfile = calloc(1024, 1);
                    realpath(fullpath, realfile);
                    unlink(fullpath);
                    link(realfile, fullpath);
                }
            }
        }
    }
    return 0;
}