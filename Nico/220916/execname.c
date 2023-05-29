// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Creare una directory chiamata exec. Scrivere un programma execname che se viene aggiunto un file
// nela directory exec interpreti il nome del file come comando con parametri, lo esegua e cancelli il file.
// es: sopo aver lanciato execname:
//  execname exec
// a seguito di questo comando:
//  touch 'exec/echo ciao mare'
// il programma stampa:
//  ciao mare
// (consiglio, usare inotify)

// implementazione: 
// 1) deve controllare se ci sono nuovi file nella directory
// 2) se c'e' nuovo file (se avviene inotify),allora legge dalla directory il nome del file, allora lancia exec con parametro
// 3) altrimenti resta in attesa di nuovi file

#include<stdio.h>
#include<sys/inotify.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h> // library for fcntl function
 
#define MAX_EVENTS 1024  /* Maximum number of events to process*/
#define LEN_NAME 16  /* Assuming that the length of the filename
won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ))
/*buffer to store the data of events*/
 
int fd,wd;
 
void sig_handler(int sig){
    /* Step 5. Remove the watch descriptor and close the inotify instance*/
    inotify_rm_watch( fd, wd );
    close( fd );
    exit( 0 );
}
 
 
int main(int argc, char **argv){
    char *path_to_be_watched;
    signal(SIGINT,sig_handler);

    path_to_be_watched = argv[1];

    /* Step 1. Initialize inotify */
    fd = inotify_init();


    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)  // error checking for fcntl
    exit(2);

    /* Step 2. Add Watch */
    wd = inotify_add_watch(fd,path_to_be_watched,IN_MODIFY | IN_CREATE | IN_DELETE);

    if(wd==-1){
            printf("Could not watch : %s\n",path_to_be_watched);
    }
    else{
    printf("Watching : %s\n",path_to_be_watched);
    }
 
 
    while(1){
        int i=0,length;
        char buffer[BUF_LEN];

        /* Step 3. Read buffer*/
        length = read(fd,buffer,BUF_LEN);

        /* Step 4. Process the events which has occurred */
        while(i<length){
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if(event->len){
                if ( event->mask & IN_CREATE ) {
                    if (!( event->mask & IN_ISDIR )) {
                        printf( "The directory %s was created.\n", event->name );
                    }
                    else {
                        printf( "The file %s was created.\n", event->name );
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    return 0;
}