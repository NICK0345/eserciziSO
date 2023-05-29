#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char s[] = "helloworld\n";
    printf("%s\n", s);
    printf("%p\n", (long long *) s);
    printf("%lld\n", *(long long *) s);
    char a[9];
    s = (long long *) s;
    memcpy(a, &((void *) *(long long *) s), 8);
    printf("%s", a );
    return 0;
}