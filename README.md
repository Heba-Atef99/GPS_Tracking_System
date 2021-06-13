# GPS_Tracking_System
This project is develop using TM4C123G LaunchPad, the system stores the coordinates of the path and displays the moved trajectory at the end using Python along with the total distance that the user moved displayed on a three digit 7-segment display.

## Functions done by the system:
1. Start reading coordinates when pushing switch 2 and the build-in GREEN LED of the launchpad is turned on to indicate the start.
2. Send the coordinates continously to PC through USB.
3. When the distance moved is bigger or equal to 100 the build-in RED LED of the launchpad is turned on.
5. Stop reading coordinates when pushing switch 1 and the build-in BLUE LED of the launchpad is turned on to indicate the end.
6. Display the calculated distance on three digit 7-segment displays.
7. Display the trajectory on a map.
