#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
    char word[9], outword[17];
    int i, len;

    printf("Intro word:");
    fgets(word, sizeof(word), stdin);
    len = strlen(word);
    if(word[len-1]=='\n')
        word[--len] = '\0';

    for(i = 0; i<len; i++){
        sprintf(outword+i*2, "%02x", word[i]);
    }
    printf("%s\n", outword);
    printf("%ld\n", strtol(outword, NULL, 16));
    printf("%p\n", (void *)strtol(outword, NULL, 16));

    long int decimalNumber,remainder,quotient;
	int j,temp;
    i=1;
	char hexadecimalNumber[100];
    decimalNumber = strtol(outword, NULL, 16);
    quotient = decimalNumber;
	while(quotient!=0) {
		temp = quotient % 16;
		//To convert integer into character
		temp = temp + 48; 
		hexadecimalNumber[i++]= temp;
		quotient = quotient / 16;
	}
	printf("Equivalent hexadecimal value of decimal number %ld: ",decimalNumber);
    // for (j = i -1 ;j> 0;j-=1)
    //     printf("%c ",((hexadecimalNumber[j])));
	for (j = i -1 ;j> 0;j-=2)
	      printf("%c",(char)((hexadecimalNumber[j]-'0')*16+(hexadecimalNumber[j-1]-'0')));
    return 0;
}