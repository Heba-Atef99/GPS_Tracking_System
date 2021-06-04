#include "functions.h"

float rad(float degree){
	//Calculates radian
	return degree*PI/180;
}
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
int distance_calc(float lat1, float lat2, float lng1, float lng2){
	//Calculates the distance between two points given their  
	//longitutes and latitudes according to Haversine Formula
	float dLat, dLng, a, c;
	int d;
	lat1 = nmea_to_map(lat1);
	lat2 = nmea_to_map(lat2);
	lng1 = nmea_to_map(lng1);
	lng2 = nmea_to_map(lng2);
	dLat = rad(lat2 - lat1); 
	dLng = rad(lng2 - lng1);
	
	a = sin(dLat / 2) * sin(dLat / 2) + cos(rad(lat1)) * cos(rad(lat2)) * sin(dLng / 2) * sin(dLng / 2);
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	d = c * R;
	
	return d;
}
