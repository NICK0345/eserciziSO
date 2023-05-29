#include <stdio.h>                                                              
#include <time.h>                                                               
                                                                                
int main(void)                                                                  
{                                                                               
  char dest[70];                                                                
  int ch;                                                                       
  time_t temp;                                                                  
  struct tm *timeptr;                                                           
                                                                                
  temp = time(NULL);                                                            
  timeptr = localtime(&temp);                                                   
  ch = strftime(dest,sizeof(dest)-1,"%a %b %d %OH:%OM:%OS %Z %EY", timeptr);                            
  printf("%d characters placed in string to make: \n \n %s", ch, dest);         
}                                                                               
   