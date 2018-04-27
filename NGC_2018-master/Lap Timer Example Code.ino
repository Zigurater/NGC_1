#include <Wire.h>
#include <EEPROM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <SoftwareSerial.h>

SoftwareSerial Thermal(3, 2);
Adafruit_7segment matrixGreen = Adafruit_7segment();
Adafruit_7segment matrixRed = Adafruit_7segment();

int photocellPin = 7;     
int photocellReading;  
int photocellBreak = 0;
int lapCount = 0;
int lapTime = 0;
int lapTimes[10];
int FastestLap = 6000;
int minLaptime = 1000;
int clockSync = 7600;
int totalTime = 0;
int TotalLaps = 3;

int heatTime = 80;
int heatInterval = 255;
char printDensity = 15; 
char printBreakTime = 15;

float timeprint;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  
  matrixGreen.begin(0x70);  // no address soldered
  matrixRed.begin(0x71);    // A1 soldered

  matrixGreen.print(10000, DEC);
  matrixRed.print(10000, DEC);

  matrixGreen.writeDisplay();
  matrixRed.writeDisplay();
  //EEPROM.put ( 0, FastestLap);

  delay(1000);

  Thermal.begin(19200); // to write to our new printer
  initPrinter();

}

void loop() {


  DisplayText(0);
 
  int Whattodo = 0;

   Whattodo = Button();
   Serial.println(Whattodo, DEC);
   if (Whattodo == 1) {
      LapTime(TotalLaps);
     }
   if (Whattodo == 2) {
       Serial.println("Set Laps");
      SetLaps(); 
      }

}

void SetLaps() {
 int l;
 int la;
 int b;
 
 DisplayText(1);

 la = analogRead(A2);
 b = analogRead(A1);
 
 while (b < 200 or b > 300) {
  l = map(la,1023,0,1,9);
  
  matrixRed.print(l, DEC);
  matrixRed.writeDisplay();

  delay(10);
  la = analogRead(A2);
  b = analogRead(A1); 
 }

 TotalLaps = l;
}


void DisplayText(int T) {
  // 1 = Laps

  if (T==0) {
   matrixGreen.writeDigitRaw(0,B01000000);
   matrixGreen.writeDigitRaw(1,B01000000);
   matrixGreen.writeDigitRaw(3,B01000000);
   matrixGreen.writeDigitRaw(4,B01000000);
   matrixGreen.writeDisplay();

   matrixRed.writeDigitRaw(0,B01000000);
   matrixRed.writeDigitRaw(1,B01000000);
   matrixRed.writeDigitRaw(3,B01000000);
   matrixRed.writeDigitRaw(4,B01000000);
   matrixRed.writeDisplay();
  }
   
  
  if (T ==1) {
   matrixGreen.writeDigitRaw(0,B00111000);
   matrixGreen.writeDigitRaw(1,B01110111);
   matrixGreen.writeDigitRaw(3,B01110011);
   matrixGreen.writeDigitRaw(4,B01101101);
   matrixGreen.writeDisplay();
  }
  
  
}

int Button() {

  int select = 0;
  
  int b = analogRead(A1);
  while (b > 900) {
   b = analogRead(A1);
  }
  
  if (b > 400 and b < 500) {
    select = 1;
   }
  if (b > 300 and b < 400) {
    select = 2;
   }
  if (b > 200 and b < 300) {
    select = 3; 
   }
  

  return select;
  
}

void initPrinter()
{
 //Modify the print speed and heat
 Thermal.write(27);
 Thermal.write(55);
 Thermal.write(7); //Default 64 dots = 8*('7'+1)
 Thermal.write(heatTime); //Default 80 or 800us
 Thermal.write(heatInterval); //Default 2 or 20us
 //Modify the print density and timeout
 Thermal.write(18);
 Thermal.write(35);
 int printSetting = (printDensity<<4) | printBreakTime;
 Thermal.write(printSetting); //Combination of printDensity and printBreakTime
 
}

void LapTime(int Laps){
 
  RaceStatus(0);
  photocellReading = 0;
  lapTime = 0;
  lapCount = 0;
  
  photocellReading = digitalRead(photocellPin);
  while (photocellReading == photocellBreak  ) {
    photocellReading = analogRead(photocellPin);
    if (analogRead(A1) >  200 and analogRead(A1) < 300) { 
       Serial.println("Back to menu");
      return; 
      }
  }
  
  matrixGreen.print((Laps), DEC);
  matrixGreen.drawColon(false);
  matrixRed.print(0, DEC);
  matrixRed.drawColon(true);
  matrixGreen.writeDisplay();
  matrixRed.writeDisplay();

  delay(1000);
  
  for (int x=0; x<10; x++) { lapTimes[x] = 0; }
  
  while (photocellReading != photocellBreak) {  // wait for start of Race 
    photocellReading = digitalRead(photocellPin);
    if (analogRead(A1) >  200 and analogRead(A1) < 300) { 
       Serial.println("Back to menu");
      return; 
      }
  }
  
  // Start LapTiming!!!

  while (lapCount < Laps) {

  matrixGreen.print((Laps - lapCount - 1), DEC);
  matrixGreen.drawColon(false);
  matrixGreen.writeDisplay();
  
  while (photocellReading != photocellBreak or lapTime < minLaptime ) {
    delayMicroseconds(clockSync);
    lapTime = lapTime+1;
    matrixRed.print(lapTime, DEC);
    matrixRed.drawColon(true);
    matrixRed.writeDisplay();
    photocellReading = digitalRead(photocellPin);
    if (analogRead(A1) >  200 and analogRead(A1) < 300) { 
       Serial.println("Back to menu");
      return; 
      }
   }

   EEPROM.get(0, FastestLap);
   if (lapTime < FastestLap) {
     EEPROM.put ( 0, lapTime);
               
   }
   lapTimes[lapCount] = lapTime; 
   lapCount++;
   lapTime = 0;
  }

  

  Thermal.println("Crazy Kart Race Results! ");
  Thermal.println("=========================");
  totalTime = 0;
  for (int l=0; l<Laps; l++){
    Thermal.print("Lap ");
    Thermal.print(l +1);
    Thermal.print(": ");
    totalTime = totalTime + lapTimes[l];
    timeprint = (float)lapTimes[l]/100;
    Thermal.print(timeprint,2);
    Thermal.println(" seconds");
  }
  Thermal.write(10);
  Thermal.print("Total: ");
  Thermal.println(TimeFormat(totalTime));
  Thermal.write(10);
  Thermal.write(10);

   
}


String TimeFormat(int t) {

  int millisec = t % 100;
  int tseconds = t /100;
  int tminutes = tseconds / 60;
  int seconds = tseconds % 60;

  String timestring = "";
  
  if (tminutes == 0) {
    timestring = String(seconds,DEC) + "." + String(millisec, DEC) + " Seconds";
  }
  if (tminutes == 1) {
    timestring = String(tminutes,DEC) + " Minute " + String(seconds,DEC) + "." + String(millisec, DEC) + " Seconds";
  }
  if (tminutes > 1) {
    timestring = String(tminutes,DEC) + " Minutes " + String(seconds,DEC) + "." + String(millisec, DEC) + " Seconds";
  }
  
  return timestring;
}


void RaceStatus(int Status) {
 if (Status == 0) {
  matrixGreen.print(10000, DEC);
  matrixRed.print(10000, DEC);
  matrixGreen.writeDisplay();
  matrixRed.writeDisplay();
  }

 if (Status == 1) {
  EEPROM.get(0, FastestLap);
  matrixGreen.print(FastestLap, DEC);
  matrixGreen.drawColon(true);
  matrixRed.print(0, DEC);
  matrixGreen.writeDisplay();
  matrixRed.writeDisplay();
  }

  
}

