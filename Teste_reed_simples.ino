//arduino bike speedometer w serial.print()
//by Amanda Ghassaei 2012
//http://www.instructables.com/id/Arduino-Bike-Speedometer/
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
*/
#define reed A0//pin connected to read switch
//storage variable
int reedVal;
void setup(){
 Serial.begin(9600);
}
void loop(){
 reedVal = analogRead(reed);//get val of A0
 Serial.println(reedVal);
 delay(10);
}
