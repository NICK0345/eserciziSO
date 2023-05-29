#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/* Start children. */
int pCount = 0;
int status;
pid_t pid;

// scrivere un programma para per lanciare parallelamente comandi
// para sleep 20 // ls -l // ps // sleep 3
// deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti

int main(int argc, char *argv[]){
    char delimitor[]="//";
    int start = 2;
    int end = 2;

    char **param;
    if(argc < 3){
        perror("command not found");
        exit(1);
    }
    while(end < argc) {
        if((strncmp(argv[end], delimitor, 2) == 0) && end <= argc-1){
            if(end - start > 1){
                param = (char **) calloc(end-start+1, sizeof(char*));
                int k = start;
                int j = 0;
                for(; j < end-start;){
                    param[j++] = argv[k++];
                }
                param[j]=NULL;
                if ((pid = fork()) < 0) {
                    perror("fork");
                    abort();
                } else if(pid == 0){
                    execvp(argv[start], param);
                    exit(0);
                }
                else{
                    pCount += 1;
                }
                free(param);
            }
            else{
                if ((pid = fork()) < 0) {
                    perror("fork");
                    abort();
                } else if(pid == 0){
                    execlp(argv[start], argv[start], NULL);
                    exit(0);
                }
                else{
                    pCount += 1;
                }
            }
            if(pCount >= 3){
                printf("pCount = %d, waiting...\n", pCount);
                pid = wait(&status);
                pCount-= 1;
            }
            start=end+1;
        }
        end+=1;
    }
    //non c'e' piu' bisogno di ricopiare, basta passare per il parametro
    if ((pid = fork()) < 0) {
        perror("fork");
        abort();
    } else if(pid == 0){
        if(start < argc){
            execvp(argv[start], &argv[start]);
        }
        else{
            execlp(argv[start], argv[start], NULL);
        }
    }
    else{
        pCount += 1;
    }
    while(pCount > 0){
        pid = wait(&status);
        pCount -=1;
    }
    return 0;
}