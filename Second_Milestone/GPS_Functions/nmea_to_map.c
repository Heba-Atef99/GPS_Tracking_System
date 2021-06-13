#include "functions.h"

float nmea_to_map(float nmea) {
	//NMEA Format: dddmm.mmmm
	//Longitude/Latitude = ddd + mm.mmmm/60
	int ddd;
	float mm;
	ddd = nmea;
	if (nmea < 100) {
		ddd = 0;
		mm = nmea;
	}
	else {
		//Calculating ddd
		int th, h, t, u, h_th;  // Thousands,hundreds,tens,units 
		u = ddd % 10;
		t = (ddd / 10) % 10;
		h = (ddd / 100) % 10;
		th = ddd / 1000;
		h_th = ddd - u - (t * 10) - (h * 100) - (th * 1000);
		ddd = (h_th * 100) + (th * 10) + h; //First 3 or 2 digits
		//Calculating mm.mmmm
		mm = nmea - (h * 100) - (th * 1000) - (h_th * 10000);
	}
	return ddd + (mm / 60);
}