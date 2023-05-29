#define read 0
#define write 1
#define open 2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
    char *syscall[3] = {"read", "write", "open"};
    int length = strlen (argv[1]);
    int isnumber = 1;
    for (int i=0;i<length; i++){
        if (!isdigit(argv[1][i])){
            isnumber = 0;
            break;
        }
    }
    for(int i = 0; i < 3; i++){
        if(strcmp(syscall[i], argv[1]) == 0){
            printf("%d\n", i);
        }
        printf("%d", atoi(argv[1]));
        // if(i == atoi(argv[1])){
        //     printf("%s\n", syscall[i]);
        // }
    }
    return(0);
}