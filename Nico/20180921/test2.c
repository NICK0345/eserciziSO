#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    for(int i = 0; i < 5; i++){
        switch (fork())
        {
        case 0:
            printf("sono figlio %d\n", i);
            exit(0);
            break;
        case -1:
            exit(1);
        default:
            printf("sono il padre\n");
            break;
        }
    }
}