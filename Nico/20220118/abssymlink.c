// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Scrivere il programma abssymlink  che ha come parametro il pathname di una directory.
// Il programma deve cercare tutti i link simbolici presenti nella directory e trasformare ogni link
// simbolico in uno equivalente che punti al pathname assoluto e non relativo.

//inazitutto devo leggere tutte le entry di una directory todo
//devo farlo puntare al pathname assoluto e non relativo

// Esercizio 2: Linguaggio C: 10 punti
// Scrivere il programma cpsymlink: che ha come parametro il pathname di una directory.
// Il programma deve cercare tutti i link simbolici presenti nella directory e sostituire ogni link simbolico
// che punta ad un file regolare con la copia del file puntato.
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *dirname = argv[1];
    DIR *dir = opendir(dirname);
    struct dirent *entry;

    while( (entry=readdir(dir)) )
    {
        struct stat sb;
        lstat(entry->d_name, &sb);
        if((sb.st_mode & __S_IFMT) == __S_IFLNK){
            //se e' un link simbolico
            char fullpath[strlen(entry->d_name)+strlen(dirname)+2];
            snprintf(fullpath, sizeof fullpath, "%s/%s", argv[1], entry->d_name);
            //questo e' se sto generando in altri directory che non sono nella working directory
            char *abspath = realpath(entry->d_name, NULL);
            unlink(entry->d_name);
            // symlink(abspath, entry->d_name);
            // printf("%s %s\n", entry->d_name, abspath);
            FILE *original = fopen(abspath, "r");
            FILE *duplicate = fopen(fullpath, "w+");
            char c;
            while((c = fgetc(original)) != EOF) fputc(c, duplicate);
            fclose(original);
            fclose(duplicate);
        }
    }
    closedir(dir);
    return 0;
}
