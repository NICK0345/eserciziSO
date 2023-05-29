#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <execs.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int pd[2][2];
    pipe(pd[0]);
    pipe(pd[1]);
    char *line = NULL;
    size_t len = 0;
    pid_t pid;

    while(getline(&line, &len, stdin) != -1) {
        printf("-->%s", line);
        pid = fork();
        if(pid == 0) {
            close(pd[0][1]);
            close(pd[1][0]);
            dup2(pd[0][0], STDIN_FILENO);
            dup2(pd[1][1], STDOUT_FILENO); // Write to the second pipe
            close(pd[0][0]);
            close(pd[1][1]);
            system_nosh(line);
            _exit(0);
        } else {
            wait(NULL);
            close(pd[0][0]);
            close(pd[1][1]);
            char f;
            ssize_t res;
            printf("a\n");
            while((res = read(pd[1][0], &f, 1)) > 0) {
                printf("%c\n", f);
                write(pd[0][1], &f, 1); // Write to the first pipe
            }
            close(pd[0][1]);
            close(pd[1][0]);
        }
    }

    int f;
    while(read(pd[1][0], &f, 1))
        write(pd[0][1], &f, 1); // Write to the first pipe

    return 0;
}

