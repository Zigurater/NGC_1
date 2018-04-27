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

//variables for "ratio green" and "ratio blue" values:
int rg;
int rb;
int rc;

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
   
  //"ratio green" and "ratio blue" are unit ratios to the red value
  rg = g / r;
  rb = b / r;
  rc = c / r;
  Serial.println("r:g:b:c = ");
  Serial.print(1);
  Serial.print(":");
  Serial.print(rg);
  Serial.print(":");
  Serial.print(rb);
  Serial.print(":");
  Serial.print(rb);

  
  //cyan (5,46,45,95) -> (1, 9.2, 9, 19)
  //yellow (43,38,30,104) -> (1, 0.8837, 0.625, 2.4186)
  //magenta (41,24,75,132) -> (1, 0.5854, 1.8293, 3.2195)
  //green (5,46,32,65) -> (1, 9.2, 6.4, 13)
  //blue (2,26,87,112) -> (1, 13, 43.5, 56)
  //red (43,3,7,44) -> (1, 0.0698, 0.1628, 1.0232)
  //pulsar (uh oh no values) -> ( :P )
  if(){ //cyan
    
  }else if(){ //yellow
    
  }else if(){ //magenta
    
  }else if(){ //green
    
  }else if(){ //blue
    
  }else if(){ //red
    
  }else if(){ //pulsar
    
  }
  
}


//Need to: 1)find what each color's ratio is, 2)actually make sure that the change in the rgb values is roughly ratio, 3)measure how much error needs to be allowed
