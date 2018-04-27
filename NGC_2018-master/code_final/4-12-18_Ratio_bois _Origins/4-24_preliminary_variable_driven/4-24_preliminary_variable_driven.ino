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
//tolerence variables to make testing easier
int rgh;
int rgl;
int rbh;
int rbl;
int rch;
int rcl;
int tolerence = 0.5;

//base rgb values that generate the ratio values (change these to calibrate "easily")
int 1r = 5;
int 1g = 46;
int 1b = 45;
int 1c = 95;

int 2r = 43;
int 2g = 38;
int 2b = 30;
int 2c = 104;

int 3r = 41;
int 3g = 24;
int 3b = 75;
int 3c = 132;

int 4r = 5;
int 4g = 46;
int 4b = 32;
int 4c = 65;

int 5r = 2;
int 5g = 26;
int 5b = 87;
int 5c = 112;

int 6r = 43;
int 6g = 3;
int 6b = 7;
int 6c = 44;

int 7r = ;
int 7g = ;
int 7b = ;
int 7c = ;

int 1rg = 1g / 1r;
int 1rb = 1b / 1r;
int 1rc = 1c / 1r;
int 2rg = 2g / 1r;
int 2rb = 2b / 1r;
int 2rc = 2c / 1r;
int 3rg = 3g / 1r;
int 3rb = 3b / 1r;
int 3rc = 3c / 1r;
int 4rg = 4g / 1r;
int 4rb = 4b / 1r;
int 4rc = 4c / 1r;
int 5rg = 5g / 1r;
int 5rb = 5b / 1r;
int 5rc = 5c / 1r;
int 6rg = 6g / 1r;
int 6rb = 6b / 1r;
int 6rc = 6c / 1r;
int 7rg = 7g / 1r;
int 7rb = 7b / 1r;
int 7rc = 7c / 1r;




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
   
  //"ratio green", "ratio blue", and "ratio clear" ("rg", "rb", and "rc") are unit ratios to the red value
  rg = g / r;
  rb = b / r;
  rc = c / r;
  Serial.println("      r:g:b:c = ");
  Serial.print(1);
  Serial.print(":");
  Serial.print(rg);
  Serial.print(":");
  Serial.print(rb);
  Serial.print(":");
  Serial.print(rc);
  Serial.println("      tolerence radius: ");
  Serial.print(tolerence);
  
  if(((9.2 - tolerence) < rg < (9.2 + tolerence)) && ((9 - tolerence) < rb < (9 + tolerence)) && ((19 + tolerence) < rc < (19 + tolerence))){ //cyan
    Serial.println("Cyan Planet");
  }else if(((0.8837 - tolerence) < rg < (0.8837 + tolerence)) && ((0.625 - tolerence) < rb < (0.625 + tolerence)) && ((2.4186 + tolerence) < rc < (2.4186 + tolerence))){ //yellow
    Serial.println("Yellow Planet");
  }else if(((0.5854 - tolerence) < rg < (0.5854 + tolerence)) && ((1.8293 - tolerence) < rb < (1.8293 + tolerence)) && ((3.2195 + tolerence) < rc < (3.2195 + tolerence))){ //magenta
    Serial.println("Magenta Planet");
  }else if(((9.2 - tolerence) < rg < (9.2 + tolerence)) && ((6.4 - tolerence) < rb < (6.4 + tolerence)) && ((13 + tolerence) < rc < (13 + tolerence))){ //green
    Serial.println("Green/Habitable Planet");
  }else if(((13 - tolerence) < rg < (13 + tolerence)) && ((43.5 - tolerence) < rb < (43.5 + tolerence)) && ((56 + tolerence) < rc < (56 + tolerence))){ //blue
    Serial.println("Blue/Gas Giant");
  }else if(((0.0698 - tolerence) < rg < (0.0698 + tolerence)) && ((0.1628 - tolerence) < rb < (0.1628 + tolerence)) && ((1.0232 + tolerence) < rc < (1.0232 + tolerence))){ //red
    Serial.println("Red/Magama Planet");
  }else if(((9.2 - tolerence) < rg < (9.2 + tolerence)) && ((9 - tolerence) < rb < (9 + tolerence)) && ((19 + tolerence) < rc < (19 + tolerence))){ //pulsar: NEED BETTER RGB VALUES (these are the cyan values)
    Serial.println("Plusar");
  }
  
}


//Need to: 1)find what each color's ratio is, 2)actually make sure that the change in the rgb values is roughly ratio, 3)measure how much error needs to be allowed
  // 1 cyan (5,46,45,95) -> (1, 9.2, 9, 19)
  // 2 yellow (43,38,30,104) -> (1, 0.8837, 0.625, 2.4186)
  // 3 magenta (41,24,75,132) -> (1, 0.5854, 1.8293, 3.2195)
  // 4 green (5,46,32,65) -> (1, 9.2, 6.4, 13)
  // 5 blue (2,26,87,112) -> (1, 13, 43.5, 56)
  // 6 red (43,3,7,44) -> (1, 0.0698, 0.1628, 1.0232)
  // 7 pulsar (uh oh no values) -> ( :P )
