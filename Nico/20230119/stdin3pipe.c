#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <execs.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    int pd[2][2];
    pipe(pd[0]);
    pipe(pd[1]);
    char *line = NULL;
    size_t len = 0;
    pid_t pid;

    // pd[0][0] -> padre legge
    // pd[1][1] -> padre scrive
    // pd[1][0] -> figlio legge
    // pd[0][1] -> figlio scrive
    int f = 1;
    while(getline(&line, &len, stdin) != -1){
        printf("-->%s\n", line);
        pid = fork();
        if(pid == 0){
            dup2(pd[1][0], STDIN_FILENO);
            dup2(pd[0][1], STDOUT_FILENO);
            close(pd[0][0]);
            close(pd[1][1]);
            close(pd[0][1]);
            close(pd[1][0]);
            // char f[1];
            // int i = 0;
            // int res;
            // printf("b\n");
            // while((res = read(pd[0][0], f, 1))>0){
            //     printf("%s\n", f);
            //     // write(pd[1][1], f, 1);
            // }
            // printf("b\n");
            // printf("helloworld\n");
            system_nosh(line);
            _exit(0);
        }
        else{
            //il padre ricopia da quello scrittura in lettura
            close(pd[0][1]);
            // close(pd[1][0]);
            wait(NULL);
            char f[1];
            int i = 0;
            int res;
            printf("a\n");
            while((res = read(pd[0][0], f, 1))>0){
                // printf("%c", f[0]);
                write(pd[1][1], f, 1);
                printf("a");
                //fflush(stdout);
            }
            printf("a\n");
            close(pd[0][0]);
            close(pd[1][1]);
        }
    }
    //le pipe non possono essere allo stesso tempo in lettura e in scrittura ho bisogno di due pipe
    // int f;
    // while(read(pd[0][0], &f, 1 > 0))
    //     write(pd[1][1], &f, 1);
    return 0;
}