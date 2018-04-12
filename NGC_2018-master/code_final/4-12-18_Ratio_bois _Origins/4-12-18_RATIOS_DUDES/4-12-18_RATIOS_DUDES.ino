#include "Adafruit_APDS9960.h"
#include <Adafruit_NeoPixel.h>
Adafruit_APDS9960 apds;
#include <Servo.h>
#define PIN            4
#define NUMPIXELS      8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int counter = 1;
unsigned long sTime1;
unsigned long sTime2;
unsigned long eTime1;
unsigned long eTime2;
unsigned long P1;
unsigned long P2;
int planettype;
int pos;
int F;
bool moving;
bool pulsar_value;
Servo myservo;  // create servo object to control a servo'
bool deployed;

void setup() {
    Serial.begin(115200);
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");
  strip.begin(); // This initializes the NeoPixel library.
  // enable color sensing mode
  apds.enableColor(true);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pos = 200;
  deployed = false;
  //moving = false;
  myservo.writeMicroseconds(2250);
  
             strip.show();
  
  //pulsar_value = wait_for_on; // What is this line supposed to do? Wait_For_On was declared as a method in the bottom. Were you intending for wait_for_one to return a boolean? You'll want to include a "()" in there if it is. -AR
}
void loop() {
 
    // create some variables to store the color data in
    uint16_t r, g, b, c;
    
    // wait for color data to be ready
    while(!apds.colorDataReady()){
      delay(5);
    }

    // get the data and print the different channels

    apds.getColorData(&r, &g, &b, &c);

    Serial.print("red: ");
    Serial.print(r);
    
    Serial.print(" green: ");
    Serial.print(g);
    
    Serial.print(" blue: ");
    Serial.print(b);
    
    Serial.print(" clear: ");
    Serial.println(c);
    Serial.println();
}
