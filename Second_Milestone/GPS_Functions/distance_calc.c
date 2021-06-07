#include "functions.h"
#include "../UART/UART.h"

float rad(float degree){
	//Calculates radian
	return degree*PI/180;
}
int distance_calc(float lat1, float lat2, float lng1, float lng2){
	//Calculates the distance between two points given their  
	//longitutes and latitudes according to Haversine Formula
	float dLat, dLng, a, c;
	int d;
	dLat = rad(lat2 - lat1); 
	dLng = rad(lng2 - lng1);
	
	a = sin(dLat / 2) * sin(dLat / 2) + cos(rad(lat1)) * cos(rad(lat2)) * sin(dLng / 2) * sin(dLng / 2);
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	d = c * R;
	
	return d;
}

int Convert_fun(char str [],char N [],char S []){
	//String str = String. valueOf(text);
	char dest[100];
	char dest2[100];
	//char N[100];
	//char S[100];
	//char n [] ="$GPGLL,3003.91254,N,03116.81201,E,163727.00,A,A*6B";
	size_t size;
	char *ret;
  const char ch = ',';
	//size = sizeof(str);
  ret = memchr(str , ch, strlen(str ));
  strcpy(dest, ret+1);
	//strncpy(dest, dest, 18);
	ret = memchr(dest , ch, strlen(dest ));
	strncpy(N, dest, 10);
  ret = memchr(dest , ch, strlen(dest ));
  strcpy(dest, ret+3);
  strncpy(S, dest, 11);	
	return 0;
}

//read $GPGLL line
void gps_read(char gps_line[100])
{
	int i = 0;
	while (1)
	{
			gps_line[i] = read_UART7();
			write_UART0(gps_line[i]);
			i++;
			if(gps_line[i - 2] == 0x0D && gps_line[i - 1] == 0x0A)
			{
				if(gps_line[4] == 'L' && gps_line[5] == 'L')
				{
					break;
				}
				i = 0;
			}			
	}
}
