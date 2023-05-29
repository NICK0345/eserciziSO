#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int name2vect(char *src, char *dest[], char sep){
    int destMIdx = 0;
    int destIdx = 0;
    int srcIdx = 0;
    dest[0] = malloc(1024);
    do{
        if(src[srcIdx]==sep){
            dest[destMIdx][destIdx]='\0';
            destMIdx++;
            dest[destMIdx] = malloc(1024);
            destIdx=0;
        }
        else
            dest[destMIdx][destIdx++] = src[srcIdx];
        srcIdx++;
    }while(src[srcIdx]!=0);
    dest[destMIdx++][++destIdx] = 0;
    dest[destMIdx] = NULL;
    return destMIdx;
}
int main(int argc, char*argv[]){
    char *commands[1024];
    int cmd_idx = -1;
    for(int i=0; i<argc; i++)
        if(i>0&&strcmp(argv[i], "//")){
            strcat(commands[cmd_idx], argv[i]);
            if(i+1<argc&&strcmp(argv[i+1], "//"))
                strcat(commands[cmd_idx], " ");
        }else
            commands[++cmd_idx] = malloc(1024);
    cmd_idx++;
    pid_t children[cmd_idx];
    for(int i=0; i<cmd_idx; i++){
        pid_t child = fork();
        if(!child){
            char *args[1024];
            name2vect(commands[i], args, ' ');
            execvp(args[0], args);
            _exit(0);
        }
        else if(child>0)
            children[i]=child;
    }
    for(int i=0; i<cmd_idx; i++){
        int status;
        waitpid(children[i], &status, WUNTRACED);
        printf("PROCESS TERMINATED\n");
    }
    exit(EXIT_SUCCESS);
}