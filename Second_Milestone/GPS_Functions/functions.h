#include "stdint.h"
#include "math.h"
#include <stdio.h>	
#include <string.h>
#include "tm4c123gh6pm.h"

#define PI 3.14159265358979323846
#define R 6378137


int distance_calc (float lat1, float lat2, float lng1, float lng2);
float nmea_to_map(float nmea);
int Convert_fun(char text [],char N [],char S []);