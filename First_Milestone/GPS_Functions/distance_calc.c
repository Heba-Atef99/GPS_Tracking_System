#include "functions.h"

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
