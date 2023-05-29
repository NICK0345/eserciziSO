// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Usando pthread_create occorre creare due thread che chiameremo produttore e consumatore.
// Il thread produttore ripetutamente genera un numero causuale, lo stampa lo mette in una variabile
// condivisa con il consumatore e attende (ritardo casuale). Il thread consumatore legge dalla variabile
// condivisa i valori e li stampa (anche il consumatore attende per un periodo casuale prima di tentare di
// leggere il valore successivo)
// Ogni valore prodotto deve venir consumato una e una sola volta, per la sincronizzazione  si richiede di
// usare eventfd in modalità EFD_SEMAPHORE.

#include <sys/eventfd.h>
#include <unistd.h>
#include <inttypes.h>           /* Definition of PRIu64 & PRIx64 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>             /* Definition of uint64_t */
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


// int eventfd(unsigned int initval, int flags);
// eventfd ritorna una fd che contiene un contatore al livello kernel, se c = 0, allora e' bloccante la lettura, altrimenti si puo' settare il valore di count a un valore > 0 con write -> semaphoro.p() = read(), semaphore write = write()
int buf = 0;
int full;
int empty;

void *consumer(){
    while(1){
        eventfd_t res;
        eventfd_read(full, &res);
        printf("ho consumato %d\n", buf);
        eventfd_write(empty, res);
        sleep(rand()%10);
    }
}

void *producer(){
    while(1){
        eventfd_t res;
        eventfd_read(empty, &res);
        buf = rand()%1000;
        printf("ho prodotto %d\n", buf);
        eventfd_write(full, res);
        sleep(rand()%10);
    }
}

int main(int argc, char *argv[]){
    full = eventfd(0, EFD_SEMAPHORE);
    empty = eventfd(1, EFD_SEMAPHORE);
    srand(time(NULL));
    pthread_t cons, prod;
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    exit(EXIT_SUCCESS);
}
       