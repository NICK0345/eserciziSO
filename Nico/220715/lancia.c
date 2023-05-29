// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Sia dato questo programma hw.c (vi viene fornito in /public/hw.c)
// #include <stdio.h>
// int main(int argc, char*argv[]) {
//  printf("hello world:");
//  for(argv++, argv--; argc > 0; argv++, argc--)
//  printf(" %s",*argv);
//  printf("\n");
//  return 0;
// }
// Il programma hw.c può essere compilato come libreria dinamica:
// gcc --shared -o hw.so hw.c
// La libreria dinamica non è un eseguibile
// $ ./hw.so 1 2 3 4
// Segmentation fault
// ma può essere caricata a tempo di esecuzione tramite dlopen. Scrivere un programma "lancia" in
// grado di eseguire il codice di hw.so
// $ ./lancia hw.so 1 2 3 4
// hello world: hw.so 1 2 3 4
// (suggerimenti: dlopen non cerca nella directory corrente, occorre passare il path assoluto della libreria.
// "main" in hw.so è una normale funzione: occorre cercare l'indirizzo della funzione main nella libreria
// ed invocarla,)

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <stdlib.h>
#include <limits.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if defined(__LP64__)
#define ElfW(type) Elf64_ ## type
#else
#define ElfW(type) Elf32_ ## type
#endif

void read_elf_header(const char* elfFile) {
  // Either Elf64_Ehdr or Elf32_Ehdr depending on architecture.
  ElfW(Ehdr) header;

  FILE* file = fopen(elfFile, "rb");
  if(file) {
    // read the header
    fread(&header, sizeof(header), 1, file);

    // check so its really an elf file
    if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
       // this is a valid elf file
    }

    // finally close the file
    fclose(file);
  }
}
int main(int argc, char *argv[]){
    void *handle;
    int (*main)(int, char *[]);
    if(argc<2)  exit(EXIT_FAILURE);
    char *error;
    char *path = realpath(argv[1], NULL);
    if(path == NULL){
        fprintf(stderr, "%s\n", "cannot resolve relative path");
        exit(EXIT_FAILURE);
    }
    handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        //non e' una liberia dinamica, devo controllare se e' un eseguibile di tipo elf
        // ElfW(Ehdr) header;
        // FILE* file = fopen(argv[1], "rb");
        // if(file) {
        //     // read the header
        //     fread(&header, sizeof(header), 1, file);

        //     // check so its really an elf file
        //     if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
        //     // this is a valid elf file
        //         if(execvp(path, &argv[1]) == -1){
        //             fprintf(stderr, "%s\n", "execvp error");
        //             exit(EXIT_FAILURE);
        //         }
        //     }
        //     else {
        //         fprintf(stderr, "%s\n", "not an ELF file");
        //         exit(EXIT_FAILURE);
        //     }
        //     // finally close the file
        //     fclose(file);
        // }
        if(execvp(path, &argv[1]) == -1){
            fprintf(stderr, "%s\n", "execvp error");
            exit(EXIT_FAILURE);
        }
    }
    else {
        dlerror();    /* Clear any existing error */

        *(void **) (&main) = dlsym(handle, "main");

        error = dlerror();
        if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
        }
        (*main)(argc-1, &argv[1]);
        dlclose(handle);
    }
    return 0;
}