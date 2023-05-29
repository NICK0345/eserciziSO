#include <sys/types.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void sighand(int signo, siginfo_t *info, void *extra)
{
    void *ptr_val = info->si_value.sival_ptr;
    long int decimalNumber,remainder,quotient;
	int j,temp;
    int i=1;
	char hexadecimalNumber[100];
    decimalNumber = (long) ptr_val;
    quotient = decimalNumber;
	while(quotient!=0) {
		temp = quotient % 16;
		temp = temp + 48; 
		hexadecimalNumber[i++]= temp;
		quotient = quotient / 16;
	}
    char c;
	for (j = i -1 ;j> 0;j-=2){
        c = (char)((hexadecimalNumber[j]-'0')*16+(hexadecimalNumber[j-1]-'0'));
        write(STDOUT_FILENO, &c, 1);
    }
    union sigval value;
    sigqueue(info->si_pid, SIGUSR2, value);
}

void endhand(int signo, siginfo_t *info, void *extra)
{
    char c = '\n';
    write(STDOUT_FILENO, &c, 1);
}

int main()
{
    struct sigaction action;
    memset(&action,0,sizeof(action));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = &sighand;
    struct sigaction end;
    memset(&end,0,sizeof(end));
    end.sa_flags = SA_SIGINFO;
    end.sa_sigaction = &endhand;
    
    if (sigaction(SIGUSR2, &action, NULL) == -1) {
        perror("sigusr: sigaction");
        return 0;
    }
    if(sigaction(SIGUSR1, &end, NULL)== -1){
        perror("sigusr: sigaction");
        return 0;
    }

    printf("Signal handler installed, waiting for signal\n");
    printf("my pid is: %d\n", getpid());

    while(1) {;}

    return 0;
}