#include "functions.h"
#include "../UART/UART.h"


float rad(float degree){
	//Calculates radian
	return degree*PI/180;
}
float distance_calc(float lat1, float lat2, float lng1, float lng2){
	//Calculates the distance between two points given their  
	//longitutes and latitudes according to Haversine Formula
	float dLat, dLng, a, c;
	float d;
	dLat = rad(lat2 - lat1); 
	dLng = rad(lng2 - lng1);
	
	a = sin(dLat / 2) * sin(dLat / 2) + cos(rad(lat1)) * cos(rad(lat2)) * sin(dLng / 2) * sin(dLng / 2);
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	d = c * R;
	return d;
}



//read $GPGLL line
void gps_read(char gps_line[100])
{
	int i = 0;
	while (1)
	{
		gps_line[i] = read_UART7();
		//if you want to display the gps readings on putty uncomment the following line
		//write_UART0(gps_line[i]);
		i++;
		if (i >= 2)
		{
			//if we have reached the end of the line in gps readings
			if (gps_line[i - 2] == 0x0D && gps_line[i - 1] == 0x0A)
			{
				if (gps_line[4] == 'L' && gps_line[5] == 'L')
				{
					break;
				}
				//to overwrite the values in the array
				i = 0;
			}		
		}			
	}
}

void convert_putty (float a)
{
	int i=0;
	char buffer[32];
	//memcpy (c,&a,32);
	int ret = snprintf(buffer, sizeof buffer, "%f", a);
	for (i = 0; i < ret; i++)
	{
		write_UART0(buffer[i]);
	}
}
