#include "Adafruit_APDS9960.h"
#include <Adafruit_NeoPixel.h>
Adafruit_APDS9960 apds;
#include <Servo.h>
#define PIN            4
#define NUMPIXELS      8
#define INT_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int Hz;
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
//int counter = 0;
int dRate= 1000;
unsigned char proximity;
bool wormhole= false;
bool pulsar_value;
Servo myservo;  // create servo object to control a servo'
bool deployed;

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
  //moving = false;
  myservo.writeMicroseconds(2250);
  apds.enableProximity(true);
  
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

    
    
 //    proximity= apds.readProximity;
    
    Serial.println("proximity: ");
    Serial.println(apds.readProximity());


if(apds.readProximity() ==1 )
{
  wormhole= true;
}

if ( apds.readProximity() > 5)
{
  wormhole= false;
  delay(500);
}

    if (wormhole == true)
    {
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
    
// These lines check the light values and sets a variable to a value based on the light values
// Values tested with Chris' phone at full brightness with colored folders
// Now testing with big boy lights in the tunnel

    if((r <= 15 && r >= 0) && (g <= 52 && g >= 40) && (b <= 40 && b >= 22) && (c <= 165)){ //green
      planettype = 6;
      //(5,46,32,65)
    }
      
    if((r <= 12 && r >= 0) && (g <= 36 && g >= 16) && (b <= 97 && b >= 77) && (c <= 165)){ //blue
      planettype = 2;
      //(2,26,87,112)
    }
  
    if((r <= 53 && r >= 33) && (g <= 13 && g >= 0) && (b <= 17 && b >= 0) && (c <= 165)){ //red
      planettype = 3;
      //(43,3,7,44)
    }

   if((r <= 52 && r >= 46) && (g <= 50 && g >= 38) && (b <= 40 && b >= 28) && (c <= 165)){ //yellow
      planettype = 4;
      //(43,38,30,104)
    }
      
    if((r <= 51 && r >= 31) && (g <= 34 && g >= 14) && (b <= 85  && b >= 65) && (c <= 165)) { //magenta
      planettype = 5;
      //(41,24,75,132)
    }
      
    if((r <= 16 && r >= 6) && (g <= 65 && g >= 52) && (b <= 65  && b >= 50) && (c <= 165)) { //cyan
      planettype = 1;
      //(5,46,45,95)
    }
      
    if((r <= 65 && r >= 50) && (g <= 85 && g >= 65) && (b <= 135  && b >= 110) && (c >= 165)) { //pulsar
      planettype = 7;
      //()
    }
    }
// Second Version of display for the planet color

  switch(planettype){ //Each line will check for a different case of the variable planttype and display based on that value
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
           delay(3000);
      break;
    case 2:
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
    case 3:
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
    case 4:
      Serial.println("Yellow Planet");
                strip.setPixelColor(0, 0, 0 ,0);
                strip.setPixelColor(1, 0, 0, 0 );
                strip.setPixelColor(2, 0, 0, 0);
                strip.setPixelColor(3, 255, 255,0 );
                strip.setPixelColor(4, 0, 0, 0);
                strip.setPixelColor(5, 0, 0, 0);
                strip.setPixelColor(6, 0, 0, 0);
                strip.setPixelColor(7, 0, 0, 0);
          strip.show();
      break;
    case 5:
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
    case 6:
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
      }else if((475 < P2) && (P2 < 525)){
        Serial.println("2 Hz");
      }else if((1975 < P2) && (P2 < 2025)){
        Serial.println(".5 Hz");
      }else if((625 < P2) && (P2 < 685)){
        Serial.println("1.5 Hz");
      }else{
        Serial.println(1/(P2/1000) && " Hz");
      }
    }
                strip.setPixelColor(0, 0, 0, 0);
                strip.setPixelColor(1, 0, 0, 0);
                strip.setPixelColor(2, 0, 0, 0);
                strip.setPixelColor(3, 0, 0, 0);
                strip.setPixelColor(4, 0, 0, 0);
                strip.setPixelColor(5, 0, 0, 0);
                strip.setPixelColor(6, 255, 255, 255);
                strip.setPixelColor(7, 0, 0, 0);
             strip.show();
       break;
    default:
      Serial.println(planettype);
}
    
  move_servo(); // call this method to move the servo 180 degrees. It will check for the magma planet on its own.
  //plusar(); // call this to calculate the frequency of the pulsar.
}

void move_servo(){
  /*if (planettype == 3 && deployed = false) {
    delay (1000);
      for (pos = 200; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      // in steps of 1 degree
      myservo.write(pos);       // tell servo to go to position in variable 'pos'
      delay(8);
      }
      deployed = true;     
      }
      */

   if (planettype == 3 && deployed == false){
    myservo.writeMicroseconds(750);
    deployed = true;
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
