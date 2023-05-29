// Esercizio 1: Linguaggio C (obbligatorio) 20 punti
// Usando il servizio inotify(7) scrivere il programma doandelete.
// Questo programma viene attivato con un unico parametro che deve essere una directory vuota
// (controllare la coerenza del parametro!).
// Quando viene aggiunto un file alla directory questo viene eseguito e cancellato.

//evento, controlla se viene aggiunto un file

#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_EVENTS 1024  /* Maximum number of events to process*/
#define LEN_NAME 16  /* Assuming that the length of the filename
won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ))
/*buffer to store the data of events*/
 
int fd,wd;
 
void sig_handler(int sig){
    inotify_rm_watch(fd, wd);
    close(fd);
    exit(0);
 
}

int main(int argc, char *argv[]){
	DIR *dir = opendir(argv[1]);
    struct dirent *entry;
    
    //se non e' una dir vuota
	while ((entry = readdir(dir))) {
		if (strcmp(entry->d_name, ".") && (strcmp(entry->d_name, ".."))){
            printf("non e' dir\n");
            closedir(dir);
            exit(1);
        }
	}
    closedir(dir);

    signal(SIGINT,sig_handler);
    fd = inotify_init();
    wd = inotify_add_watch(fd, argv[1], IN_MODIFY | IN_CREATE | IN_DELETE);

    while(1){
        int i=0,length;
        char buffer[BUF_LEN];
        length = read(fd,buffer,BUF_LEN);
        while(i<length){
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
                if(event->len){
                    int st;
                    if((event->mask & IN_CREATE)&& !(event->mask & IN_ISDIR)){
                        char *s = event->name;
                        int count = 0;
                        char *fullpath = calloc(strlen(argv[1])+strlen(event->name)+2, sizeof(char));
                        strcat(fullpath, argv[1]);
                        strcat(fullpath, "/");
                        strcat(fullpath, event->name);
                        for(i = 0;s[i] != '\0';i++){
                            if (s[i] == ' ' && s[i+1] != ' ')
                                count++;    
                        }
                        count++;
                        char **para = calloc(count+1, sizeof(char *));
                        for(i = 0; i < count; i++){
                            para[i] = (i==0)? strtok(s, " ") : strtok(NULL, " ");
                        }
                        char *program = para[0];
                        para[count] = NULL;
                        switch (fork()){
                            case 0:
                                execvp(program, para);
                                break;
                            case -1:
                                exit(1);
                            default:
                                wait(&st);
                                free(para);
                                unlink(fullpath);
                        }
                    }
                }
            i += EVENT_SIZE + event->len;
        }
    }
    return 0;
}
