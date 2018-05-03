#include "Adafruit_APDS9960.h"
#include <Adafruit_NeoPixel.h>
Adafruit_APDS9960 apds;
#include <Servo.h>
#define PIN            4
#define NUMPIXELS      8
#define INT_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//pulsar variables (this code concept comes from "Pulsar_test_code.ino" in the "color strip test" folder)
int Hz;
int dRate;
int showstart;
int secondsshowing = 5;
unsigned long sTime2;
unsigned long eTime2;
unsigned long P2;
int counter = 1;
int planettype;
int pos;
int F;
unsigned char proximity;
bool wormhole = false;
bool pulsar_value;
Servo myservo;  // create servo object to control a servo'
bool deployed;



int frame = 1;
int r1;
int g1;
int b1;
int c1;
int r2;
int g2;
int b2;
int c2;
int r3;
int g3;
int b3;
int c3;
int r4;
int g4;
int b4;
int c4;
int r5;
int g5;
int b5;
int c5;

int averageR;
int averageG;
int averageB;
int averageC;



void setup() {
  Serial.begin(115200);
  pinMode(INT_PIN, INPUT_PULLUP);
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
  myservo.writeMicroseconds(2250);
  apds.enableProximity(true);
  strip.show();
}
void loop() {
    // create some variables to store the color data in
    uint16_t r, g, b, c;
    // wait for color data to be ready
    while(!apds.colorDataReady()){
      delay(5);
    }
   // get the data and print the different channels
   //proximity = apds.readProximity;
    Serial.println("proximity: ");
    Serial.println(apds.readProximity());
    
  if(frame == 1){
    r1 = r;
    g1 = g;
    b1 = b;
    c1 = c;
    frame++;
    Serial.println("frame: ");
    Serial.print(frame);
  }else if(frame == 2){
    r2 = r;
    g2 = g;
    b2 = b;
    c2 = c;
    frame++;
    Serial.println("frame: ");
    Serial.print(frame);
  }else if(frame == 3){
    r3 = r;
    g3 = g;
    b3 = b;
    c3 = c;
    frame++;
    Serial.println("frame: ");
    Serial.print(frame);
  }else if(frame == 4){
    r4 = r;
    g4 = g;
    b4 = b;
    c4 = c;
    frame++;
    Serial.println("frame: ");
    Serial.print(frame);
  }else if(frame == 5){
    r4 = r;
    g5 = g;
    b5 = b;
    c5 = c;
    frame++;
    Serial.println("frame: ");
    Serial.print(frame);
  }else if(frame == 6){
    averageR = ((r1 + r2 + r3 + r4 + r5) / 5);
    averageG = ((g1 + g2 + g3 + g4 + g5) / 5);
    averageB = ((b1 + b2 + b3 + b4 + b5) / 5);
    averageC = ((c1 + c2 + c3 + c4 + c5) / 5);
    Serial.println("averageR: ");
    Serial.print(averageR);
    Serial.println("averageG: ");
    Serial.print(averageG);
    Serial.println("averageB: ");
    Serial.print(averageB);
    Serial.println("averageC: ");
    Serial.print(averageC);
  }
}


