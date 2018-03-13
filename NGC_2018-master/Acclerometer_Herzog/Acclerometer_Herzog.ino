//Analog Accerometer w Serial
//by Amanda Ghassaei
//https://www.instructables.com/id/Use-an-Accelerometer-and-Gyroscope-with-Arduino/
//August 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C


 //setup up accerleation variables
 int xAcc;
 int yAcc;
 int zAcc;
 bool moving;
 
 int zero = 282;//this was the zero point value for my accelerometer, your board may be slightly different.  see the comment below for calculating this with your own board.

void setup(){
  Serial.begin(115200);//set up serial
}

void loop(){
  
  //read values
  xAcc = analogRead(A1);
  yAcc = analogRead(A2);
  zAcc = analogRead(A3);
  
  /**
  if you want to determine the zero point value of your board, 
  comment out the last eight lines of this loop and uncomment the lines below.
  Hold the board parallel to the ground and watch the serial monitor, 
  the xAcc and yAcc values will hover around a common value, 
  this is your "zero" value.  Change the value of the variable "zero" above.
  **/
//print values
//Serial.print("xAcc ");
//Serial.println(xAcc);
//Serial.print("yAcc ");
//Serial.println(yAcc);
Serial.print("zAcc ");
Serial.println(zAcc);
Serial.println(moving);
delay(300);//wait
  
  //print values
//Serial.print("xAcc ");
//Serial.println(zero-xAcc);
//Serial.print("yAcc ");
//Serial.println(zero-yAcc);
//Serial.print("zAcc ");
//Serial.println(zero-zAcc);
//Serial.println(" ");
//delay(500);//wait

if ((zAcc > 385)|| (zAcc < 370)){
  moving = true;
}
if (370 < zAcc < 385){
  moving = false;
}
}
