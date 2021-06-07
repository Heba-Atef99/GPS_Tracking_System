#include "functions.h"
uint8_t Convert_fun(char str [],char N[],char S[]){
	char dest[60];
	char dest2[60];
	char *ret;
  const char ch = ',';
  ret = memchr(str , ch, strlen(str ));
  strcpy(dest, ret+1);
	ret = memchr(dest , ch, strlen(dest ));
	strncpy(N, dest, 10);
  ret = memchr(dest , ch, strlen(dest ));
  strcpy(dest, ret+3);
  strncpy(S, dest, 11);	
	ret = memchr(N , ch, strlen(N ));
	
	return (uint8_t)!ret;
}