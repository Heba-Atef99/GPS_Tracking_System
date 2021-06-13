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
	//reading examples
	//30.065203, 31.279925
	//$GPGLL,3003.91220,N,03116.79546,E,102551.00,A,A*6F
	//30.065269, 31.279811
	//$GPGLL,3003.91620,N,03116.78874,E,102612.00,A,A*62
	
	//decalre all variables
	char gps_line [100];
  char lat[20], lng[20];
	uint8_t result;
	float long_1, lat_1, long_2, lat_2;
	float distance = 0;
	float dummy_distance = 0;
	uint8_t index = 0;

	// To start when switch 2 (which is on the same line as reset button) is ON
	while((GPIO_PORTF_DATA_R & 0x01) == 1){};
		
	while(1)
	{
		//read from gps
		gps_read(gps_line);
		
		//extract longitude & latitude of the gps reading
		result = Convert_fun(gps_line, lat, lng);
		
		if (result == 1 && index == 0)
		{
			index++;
			//turn on blue led to assure that the gps is starting to get correct readings
			//led_finish();
			GPIO_PORTF_DATA_R |= 0x08;
			// delay 2 seconds
	    //Systick_Wait_Multiples_1ms(20);
	    // green led off
     	//GPIO_PORTF_DATA_R &= ~0x08;

			long_1 = atof(lng);
	    lat_1 = atof(lat);
			
			//convert nmea to map coordinates
			long_1 = nmea_to_map(long_1);
	    lat_1 = nmea_to_map(lat_1);
			
			//display the first point coordinates on putty
			convert_putty(lat_1);
			write_UART0('\r');
			write_UART0('\n');
			convert_putty(long_1);
			write_UART0('\r');
			write_UART0('\n');
		}
		
		
		else if (result == 1)
		{
			long_2 = atof(lng);
	    lat_2 = atof(lat);
			//GPIO_PORTF_DATA_R &= ~0x08;
			//convert nmea to map coordinates
			long_2 = nmea_to_map(long_2);
	    lat_2 = nmea_to_map(lat_2);
			
			//calculate distance
			dummy_distance = distance_calc(lat_1, lat_2, long_1, long_2);
			distance = distance + dummy_distance;
			convert_putty(distance);
			write_UART0('\r');
			write_UART0('\n');

			//display the second point coordinates on putty
			convert_putty(lat_2);
			write_UART0('\r');
			write_UART0('\n');
			convert_putty(long_2);
			write_UART0('\r');
			write_UART0('\n');

			//display distance on putty
			/*convert_putty(lat_2);
			write_UART0(distance);
			write_UART0('\r\n');*/
			
			//check the red led
			led_100distance(distance);
			
			//save the second point in the first point
			long_1 = long_2;
	    lat_1 = lat_2;		  
		}
		
		//wait some time till the next reading
		Systick_Wait_Multiples_1ms(1700);
		
		// to finish reading when switch 1 in on and presesnt the distance on 7-segment
		if((GPIO_PORTF_DATA_R & 0x10) == 0)
			break;
	}
	
	// turn blue led on and off when finished
	led_finish();
	
	while (1)
	{
		//display the distance on seven segment
		Seven_Segment(distance);
		
		//to finish the whole program
		if((GPIO_PORTF_DATA_R & 0x10) == 0)
			break;
	}
}
