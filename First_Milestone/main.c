#include "stdint.h"
#include "GPS_Functions/functions.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"


void SystemInit()
{
	//initalize GPIO
	init_GPIO_portA();
	init_GPIO_portB();
	init_GPIO_portF();
}
int main()
{
	int y1, y2, y3;
	float lat1, lng1, lat2, lng2;
	// Website used for debugging: https://www.nmeagen.org/
	
	while(1)
	{
		//Try one case at a time
		
		// Test case 1
		// Distance = 165.26
		lat1 = nmea_to_map(3003.918);
		lng1 = nmea_to_map(03116.622);
		lat2 = nmea_to_map(3003.834);
		lng2 = nmea_to_map(03116.657);
		y1 = distance_calc(lat1, lat2, lng1, lng2);
		Seven_Segment(y1);
		
		
		/*// Test case 2
		// Distance = 58.07
		lat1 = nmea_to_map(5231.446);
		lng1 = nmea_to_map(01324.735);
		lat2 = nmea_to_map(5231.421);
		lng2 = nmea_to_map(01324.766);
		y2 = distance_calc(lat1, lat2, lng1, lng2);
		Seven_Segment(y2);
		*/
		
		/*// Test case 3
		// Distance = 17.7
		lat1 = nmea_to_map(2901.286);
		lng1 = nmea_to_map(00930.556);
		lat2 = nmea_to_map(2901.279);
		lng2 = nmea_to_map(00930.564);
		y3 = distance_calc(lat1, lat2, lng1, lng2);
		Seven_Segment(y3);
		*/
  }
}