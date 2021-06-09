#include "GPS_Functions/functions.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"
#include "UART/UART.h"

void SystemInit()
{
	//initalize GPIO
	//init_GPIO_portA();
	init_GPIO_portB();
	init_GPIO_portF();

  init_UART0();
  init_UART7();
}

int main(void)
{	
	//30.065203, 31.279925
	//$GPGLL,3003.91220,N,03116.79546,E,102551.00,A,A*6F
	//30.065269, 31.279811
	//$GPGLL,3003.91620,N,03116.78874,E,102612.00,A,A*62
	//decalre all variables
	
	char gps_line [100];
  char	lat[20], lng[20];
	uint8_t result;
	//uint8_t pc_command;
	//uint16_t index;
	float long_1, lat_1, long_2, lat_2;
	uint32_t distance = 0;
	//float points [2][1000];

	// To start when switch 2 which is on the same line as reset button is ON
	while((GPIO_PORTF_DATA_R & 0x01) ==1){};
		
	while(1)
	{
		
		//read from gps
		gps_read(gps_line);
		
		//extract longitude & latitude of the gps reading
		result = Convert_fun(gps_line, lat, lng);
		
		/*
		if(index == 0)
		{
		char gps_line [] = "$GPGLL,3003.91220,N,03116.79546,E,102551.00,A,A*6F";
		//extract longitude & latitude of the gps reading
		result = Convert_fun(gps_line, lat, lng);
		}
		else if(index == 1)
		{
					char gps_line [] = "$GPGLL,3003.91620,N,03116.78874,E,102612.00,A,A*62";
		//extract longitude & latitude of the gps reading
		result = Convert_fun(gps_line, lat, lng);

		}
		index++;
		*/
		if (result == 1 && long_1 == 0)
		{
				led_finish();

			long_1 = atof(lng);
	    lat_1 = atof(lat);
			
			//convert nmea to map coordinates
			long_1 = nmea_to_map(long_1);
	    lat_1 = nmea_to_map(lat_1);
			
			//save the coordinates in an array for trajictory
			/*if(index < 1000)
			{
				points[0][index] = lat_1;
			  points[1][index] = long_1;
			  index++;
			}*/
		}
		
		
		else if (result == 1)
		{
			long_2 = atof(lng);
	    lat_2 = atof(lat);
			
			//convert nmea to map coordinates
			long_2 = nmea_to_map(long_2);
	    lat_2 = nmea_to_map(lat_2);
			
			//calculate distance
			distance += distance_calc(lat_1, lat_2, long_1, long_2);
			convert_putty(lat_1);
			write_UART0('\r\n');
			convert_putty(long_1);
			write_UART0('\r\n');
			convert_putty(lat_2);
			write_UART0('\r\n');
			convert_putty(long_2);
			write_UART0('\r\n');
			//write_UART0(distance);
			//write_UART0('\n');
			/*write_UART0(lat_1);
			write_UART0(long_1);
			write_UART0(lat_2);
			write_UART0(long_2);
*/
//			//display the distance
//			Seven_Segment(distance);
			
			//check the led
			led_100distance(distance);
			
			//save the second point in the first point
			long_1 = long_2;
	    lat_1 = lat_2;
		  
			//save the coordinates in an array for trajictory
			/*if(index < 1000)
			{
				points[0][index] = lat_1;
				points[1][index] = long_1;
				index++;
		  }*/
		}
		
		//wait a second
		Systick_Wait_Multiples_1ms(300);
		
		// to finish when switch 1 in on
		if((GPIO_PORTF_DATA_R & 0x10) == 0)
			break;
	}
	
	// turn blue led on and off when finished
	led_finish();
	
	while (1)
	{
		//display the distance

		Seven_Segment(distance);
		
		if((GPIO_PORTF_DATA_R & 0x10) == 0)
			break;
	}
	/*while(1)
	{
		if(read_UART0() == 'U')
		{
			
		}
	}*/
}
