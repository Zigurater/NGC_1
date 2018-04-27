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
int planettype = 0;
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
int tolerence = 0.1;

//CALIBRATION VARIABLES. base rgb values that generate the ratio values.
//1=cyan, 2=yellow, 3=magenta, 4=green, 5=blue, 6=red, 7=pulsar
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

int 7r = 47;
int 7g = 65;
int 7b = 85;
int 7c = 185;

int 1rg = 1g / 1r;
int 1rb = 1b / 1r;
int 1rc = 1c / 1r;
int 2rg = 2g / 2r;
int 2rb = 2b / 2r;
int 2rc = 2c / 2r;
int 3rg = 3g / 3r;
int 3rb = 3b / 3r;
int 3rc = 3c / 3r;
int 4rg = 4g / 4r;
int 4rb = 4b / 4r;
int 4rc = 4c / 4r;
int 5rg = 5g / 5r;
int 5rb = 5b / 5r;
int 5rc = 5c / 5r;
int 6rg = 6g / 6r;
int 6rb = 6b / 6r;
int 6rc = 6c / 6r;
int 7rg = 7g / 7r;
int 7rb = 7b / 7r;
int 7rc = 7c / 7r;




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
  
  if(((1rg - tolerence) < rg < (1rg + tolerence)) && ((1rb - tolerence) < rb < (1rb + tolerence)) && ((1rc - tolerence) < rc < (1rc + tolerence))){ //cyan
    planettype = 1;
  }else if(((2rg - tolerence) < rg < (2rg + tolerence)) && ((2rb - tolerence) < rb < (2rb + tolerence)) && ((2rc - tolerence) < rc < (2rc + tolerence))){ //yellow
    planettype = 2;
  }else if(((3rg - tolerence) < rg < (3rg + tolerence)) && ((3rb - tolerence) < rb < (3rb + tolerence)) && ((3rc - tolerence) < rc < (3rc + tolerence))){ //magenta
    planettype = 3;
  }else if(((4rg - tolerence) < rg < (4rg + tolerence)) && ((4rb - tolerence) < rb < (4rb + tolerence)) && ((4rc - tolerence) < rc < (4rc + tolerence))){ //green
    planettype = 4;
  }else if(((5rg - tolerence) < rg < (5rg + tolerence)) && ((5rb - tolerence) < rb < (5rb + tolerence)) && ((5rc - tolerence) < rc < (5rc + tolerence))){ //blue
    planettype = 5;
  }else if(((6rg - tolerence) < rg < (6rg + tolerence)) && ((6rb - tolerence) < rb < (6rb + tolerence)) && ((6rc - tolerence) < rc < (6rc + tolerence))){ //red
    planettype = 6;
  }else if(((7rg - tolerence) < rg < (7rg + tolerence)) && ((7rb - tolerence) < rb < (7rb + tolerence)) && ((7rc - tolerence) < rc < (7rc + tolerence))){ //pulsar
    planettype = 7;
  }

  switch(planettype){
    case 0:
      Serial.println("nothing to report, boss");
      break;
    case 1:
      Serial.println("Cyan Planet");
        strip.setPixelColor(0, 0, 255, 255);
        strip.setPixelColor(1, 0, 0, 0);
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
        strip.setPixelColor(4, 0, 0, 0);
        strip.setPixelColor(5, 0, 0, 0);
        strip.setPixelColor(6, 0, 0, 0);
        strip.setPixelColor(7, 0, 0, 0);
        strip.show();
      break;
    case 2:
      Serial.println("Yellow Planet");
        strip.setPixelColor(0, 0, 0 ,0);
        strip.setPixelColor(1, 0, 0, 0 );
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 255, 255, 0);
        strip.setPixelColor(4, 0, 0, 0);
        strip.setPixelColor(5, 0, 0, 0);
        strip.setPixelColor(6, 0, 0, 0);
        strip.setPixelColor(7, 0, 0, 0);
        strip.show();
      break;
    case 3:
      Serial.println("Magenta Planet");
        strip.setPixelColor(0, 0, 0, 0);
        strip.setPixelColor(1, 0, 0, 0);
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
        strip.setPixelColor(4, 255, 0, 255);
        strip.setPixelColor(5, 0, 0, 0);
        strip.setPixelColor(6, 0, 0, 0);
        strip.setPixelColor(7, 0, 0, 0);
        strip.show();
      break;
    case 4:
      Serial.println("Green/Habitable Planet");
        strip.setPixelColor(0, 0, 0, 0);
        strip.setPixelColor(1, 0, 0, 0);
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
        strip.setPixelColor(4, 0, 0, 0);
        strip.setPixelColor(5, 0, 255, 0);
        strip.setPixelColor(6, 0, 0, 0);
        strip.setPixelColor(7, 0, 0, 0);
        strip.show();
      break;
    case 5:
      Serial.println("Blue/Gas Giant");
        strip.setPixelColor(0, 0, 0, 0);
        strip.setPixelColor(1, 0, 0, 255);
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
        strip.setPixelColor(4, 0, 0, 0);
        strip.setPixelColor(5, 0, 0, 0);
        strip.setPixelColor(6, 0, 0, 0);
        strip.setPixelColor(7, 0, 0, 0);
        strip.show();
      break;
    case 6:
      Serial.println("Red/Magama Planet");
        strip.setPixelColor(0, 0, 0, 0);
        strip.setPixelColor(1, 0, 0, 0);
        strip.setPixelColor(2, 255, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
        strip.setPixelColor(4, 0, 0, 0);
        strip.setPixelColor(5, 0, 0, 0);
        strip.setPixelColor(6, 0, 0, 0);
        strip.setPixelColor(7, 0, 0, 0);
        strip.show();
      break;
    case 7:
      Serial.println("Plusar");
         if ((c < 100) && (counter == 1)){
          counter = counter + 1;
         }     
         if ((c > 100) && (counter == 2)){
          sTime2 = millis();
          counter = counter + 1;
         }
         if ((c < 100) && (counter == 3)){
          eTime2 = millis();
          counter = counter + 1;
          P2 = (eTime2 - sTime2);
          Serial.println("Period is ");
          if ((975 < P2) && (P2 < 1025)){
            Serial.println("1 Hz");
            Hz = 1;
          }else if((475 < P2) && (P2 < 525)){
            Serial.println("2 Hz");
            Hz = 2;
          }else if((1975 < P2) && (P2 < 2025)){
            Serial.println(".5 Hz");
            Hz = 0.5;
          }else if((625 < P2) && (P2 < 685)){
            Serial.println("1.5 Hz");
            Hz = 1.5;
          }else{
            Serial.println(1/(P2/1000) && " Hz");
          }
          if (Hz == 0.5) {
            dRate = 2000;
          }else if (Hz == 1) {
            dRate = 1000;
          }else if (Hz == 1.5) {
            dRate = 666;
          }else if (Hz == 2) {
            dRate = 500;
          }
        }
     break;
  }
}

void move_servo(){
   if (planettype == 3 && deployed == false){
    myservo.writeMicroseconds(750);
    deployed = true;
   }
}

void pulsar() {
  if((counter >= 4) && (counter <= 9)){
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.setPixelColor(2, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(6, 255, 255, 255);
    strip.setPixelColor(7, 0, 0, 0);
    
    strip.show();
    delay(dRate);
    
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.setPixelColor(2, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(7, 0, 0, 0);
    
    strip.show();
    delay(dRate);

    counter++;
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

//Second round of offical, ideal rgbc value testing (started on 4-26-18)
  // 1 cyan (7, 57-60, 44-50, 104-112)
  // 2 yellow (49, 50, 33, 122)
  // 3 magenta ()
  // 4 green ()
  // 5 blue ()
  // 6 red ()
  // 7 pulsar (47, 65, 85, 185)
