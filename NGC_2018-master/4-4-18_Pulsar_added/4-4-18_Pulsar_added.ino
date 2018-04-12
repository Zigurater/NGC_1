#include "Adafruit_APDS9960.h"
#include <Adafruit_NeoPixel.h>
Adafruit_APDS9960 apds;
#include <Servo.h>
#define PIN            4
#define NUMPIXELS      8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int counter = 0;
unsigned long sTime1;
unsigned long sTime2;
unsigned long eTime1;
unsigned long eTime2;
unsigned long P1;
unsigned long P2;
int planettype;
int pos = 180;
int F;
bool moving;
bool pulsar_value;
Servo myservo;  // create servo object to control a servo'

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
  //moving = false;
  
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

// Values tested with Chris' phone at full brightness with colored folders

    if((g <= 60 && g >= 45) && (r <= 11 && r >= 5) && (b <= 45 && b >= 30) && (c <= 100 && c >= 80)){ // These lines check the light values and sets a variable to a value based on the light values
      planettype = 1;
      }
      
    if((g <= 40 && g >= 28) && (r <= 10 && r >= 2) && (b <= 120 && b >= 90) && (c <= 150 && c >= 110)){
      planettype = 2;
      }
  
    if((g <= 20 && g >= 3) && (r <= 70 && r >= 45) && (b <= 20 && b >= 8) && (c <= 65 && c >= 50)){
      planettype = 3;
      }

   if((g <= 60 && g >= 40) && (r <= 60 && r >= 51) && (b <= 55 && b >= 35) && (c <= 145 && c >= 125)){
      planettype = 4;
      }
      
    if((g <= 40 && g >= 28) && (r <= 60 && r >= 45) && (b <=105  && b >= 90) && (c <= 175 && c >= 155)) {
      planettype = 5;
      }
      
    if((g <= 65 && g >= 52) && (r <= 16 && r >= 6) && (b <=65  && b >= 50) && (c <= 120 && c >= 105)) {
      planettype = 6;
      }
      
    if((g <= 85 && g >= 65) && (r <= 65 && r >= 50) && (b <= 135  && b >= 110) && (c <= 245 && c >= 220)) {
      //plusar();
      planettype = 7;
  }

// Second Version of display for the planet color

  switch(planettype){ //Each line will check for a different case of the variable planttype and display based on that value
    case 1:
      Serial.println("Green/Habitable Planet");
         strip.setPixelColor(0, 0, 255, 0);
                strip.setPixelColor(1, 0, 255, 0);
                strip.setPixelColor(2, 0, 255, 0);
                strip.setPixelColor(3, 0, 255, 0);
                strip.setPixelColor(4, 0, 255, 0);
                strip.setPixelColor(5, 0, 255, 0);
                strip.setPixelColor(6, 0, 255, 0);
                strip.setPixelColor(7, 0, 255, 0);
             strip.show();
      break;
    case 2:
      Serial.println("Blue/Gas Giant");
       strip.setPixelColor(0, 0, 0, 255);
                strip.setPixelColor(1, 0, 0, 255);
                strip.setPixelColor(2, 0, 0, 255);
                strip.setPixelColor(3, 0, 0, 255);
                strip.setPixelColor(4, 0, 0, 255);
                strip.setPixelColor(5, 0, 0, 255);
                strip.setPixelColor(6, 0, 0, 255);
                strip.setPixelColor(7, 0, 0, 255);
             strip.show();
      break;
    case 3:
      Serial.println("Red/Magama Planet");
       strip.setPixelColor(0, 255, 0, 0);
                strip.setPixelColor(1, 255, 0, 0);
                strip.setPixelColor(2, 255, 0, 0);
                strip.setPixelColor(3, 255, 0,0);
                strip.setPixelColor(4, 255, 0, 0);
                strip.setPixelColor(5, 255, 0, 0);
                strip.setPixelColor(6, 255, 0, 0);
                strip.setPixelColor(7, 255, 0, 0);
             strip.show();
      break;
    case 4:
      Serial.println("Yellow Planet");
       strip.setPixelColor(0, 255, 255 ,0);
                strip.setPixelColor(1, 255, 255,0 );
                strip.setPixelColor(2, 255, 255,0);
                strip.setPixelColor(3, 255,255,0);
                strip.setPixelColor(4, 255, 255,0);
                strip.setPixelColor(5, 255, 255,0);
                strip.setPixelColor(6, 255, 255,0);
                strip.setPixelColor(7, 255,  255,0);
      break;
    case 5:
      Serial.println("Magenta Planet");
       strip.setPixelColor(0, 255, 0, 255);
                strip.setPixelColor(1, 255, 0, 255);
                strip.setPixelColor(2, 255, 0, 255);
                strip.setPixelColor(3, 255, 0,255);
                strip.setPixelColor(4, 255, 0, 255);
                strip.setPixelColor(5, 255, 0, 255);
                strip.setPixelColor(6, 255, 0, 255);
                strip.setPixelColor(7, 255, 0, 255);
      break;
    case 6:
      Serial.println("Cyan Planet");
       strip.setPixelColor(0, 0, 255, 255);
                strip.setPixelColor(1, 0, 255, 255);
                strip.setPixelColor(2, 0, 255, 255);
                strip.setPixelColor(3, 0, 255, 255);
                strip.setPixelColor(4, 0, 255, 255);
                strip.setPixelColor(5, 0, 255, 255);
                strip.setPixelColor(6, 0, 255, 255);
                strip.setPixelColor(7, 0, 255, 255);
      break;
	  case 7:
	    Serial.println("Plusar");

           if ((c > 100) && (counter < 1))
                {sTime1 = millis();
                counter = counter + 1;
                }
          
             if ((c < 100) && (counter == 1))
               { eTime1 = millis();
                counter = counter + 1;
                   P1 = (eTime1 - sTime1) ;
               /* Serial.println("Period is ");
                Serial.println(P1);
                Serial.println(eTime1);
                Serial.println(sTime1);
               }
               */
               }
             if ((c > 100) && (counter == 2)){
                sTime2 = millis();
                counter = counter + 1;
             }
          
             if ((c < 100) && (counter == 3)){
               eTime2 = millis();
               counter = counter + 1;
                   P2 = (eTime2 - sTime2) ;
                         Serial.println("Period is ");
                if ((975 < P2) && (P2 < 1025))
                {
                Serial.println("1 Hz");
                  }
                else if((475 < P2) && (P2 < 525))
               {
                Serial.println("2 Hz");
              }
                  else if((1975 < P2) && (P2 < 2025))
                {
                Serial.println(".5 Hz");
                
               }
                   else if((625 < P2) && (P2 < 685))
              {
                Serial.println("1.5 Hz");
              }
               }
                strip.setPixelColor(0, 255, 255, 255);
                strip.setPixelColor(1, 255, 255, 255);
                strip.setPixelColor(2, 255, 255, 255);
                strip.setPixelColor(3, 255, 255, 255);
                strip.setPixelColor(4, 255, 255, 255);
                strip.setPixelColor(5, 255, 255, 255);
                strip.setPixelColor(6, 255, 255, 255);
                strip.setPixelColor(7, 255, 255, 255);
             strip.show();
       break;
    default:
      Serial.println(planettype);
}

/*
    // First version of display for the planet color
     if(planettype == 1){
      Serial.println("Green/Habitable Planet");
      }
    if(planettype == 2) {
      Serial.println("Blue/Gas Giant");
      }
    if(planettype == 3) {
      Serial.println("Red/Magama Planet");
      }
    if(planettype == 4){
      Serial.println("Yellow Planet");
      }
    if(planettype == 5) {
      Serial.println("Magenta Planet");
      }
    if(planettype == 6) {
      Serial.println("Cyan Planet");
      }
    if(planettype == 7) {
      Serial.println("Pulsar");
      }
 */
  delay(500);

  move_servo(); // call this method to move the servo 180 degrees. It will check for the magma planet on its own.
  //plusar(); // call this to calculate the frequency of the pulsar.
}
void move_servo(){
  if (planettype == 3) {
    delay (1000);
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      // in steps of 1 degree
      myservo.write(pos);       // tell servo to go to position in variable 'pos'
      delay(8);
      }     
      }
  }
// End of RGB code

// Start of Pulsar Code

// What the Pulsar code needs to do
// 1) Read bright white light values
// 2) When a certain value is read start a timer (ex. start timer when light value = 800)
// 3) End that timer when that value is read again
// 4) Start a second timer when step 3 happens
// 5) End that timer when that value is reached again
// 6) Repeat steps 1-5 for multiple trials and store these values has interger variables
// 7) Add up values from first timer and divide by number of trials
// 8) Add up values from second timer and divide by number of trials
// 9) Add up these averages
// 10) Divide 1 by that value to obtain frequency
/*
void plusar(){
  while (!moving){
    if (planettype == 7){
    wait_for_on() // Where is this method defined? -AR
    }
    if (pulsar_value){
      //write time value to something
      wait_for_off() // Where is this method defined? -AR
    }
    if (moving){
      break;
    }
    }
    }
*/
