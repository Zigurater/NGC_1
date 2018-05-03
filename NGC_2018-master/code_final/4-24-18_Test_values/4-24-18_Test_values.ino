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
  if(apds.readProximity() ==1 ){
     wormhole = true;
     }

  if ( apds.readProximity() > 5){
    wormhole = false;
    delay(500);
  }

  if (wormhole == true){
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

    if((r <= 10 && r >= 0) && (g <= 70 && g >= 60) && (b <= 45 && b >= 35) && (c <= 111)){ //green
      planettype = 6;
      //(8,68,42,109)
    }
      
    if((r <= 10 && r >= 0) && (g <= 42 && g >= 33) && (b <= 120 && b >= 110) && (c <= 145)){ //blue
      planettype = 2;
      //(3,35,110,141)
    }
  
    if((r <= 53 && r >= 33) && (g <= 13 && g >= 0) && (b <= 17 && b >= 0) && (c <= 165)){ //red
      planettype = 3;
      //(43,3,7,44)
    }

   if((r <= 60 && r >= 50) && (g <= 55 && g >= 40) && (b <= 40 && b >= 30) && (c <= 160)){ //yellow
      planettype = 4;
      //(51,48,34,128)
    }
      
    if((r <= 55 && r >= 40) && (g <= 40 && g >= 20) && (b <= 100  && b >= 76) && (c <= 190)) { //magenta
      planettype = 5;
      //(45,25,76,141)
    }
      
    if((r <= 15 && r >= 5) && (g <= 75 && g >= 65) && (b <= 70  && b >= 60) && (c <= 165)) { //cyan
      planettype = 1;
      //(7,70,66,131)
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
        strip.setPixelColor(3, 255, 255, 0);
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
      }
      else if (Hz == 1) {
        dRate = 1000;
      } 
      else if (Hz == 1.5) {
        dRate = 666;
      } 
      else if (Hz == 2) {
        dRate = 500;
      }
      showstart = millis();
      pulsar();
      if((millis() - showstart) >= (secondsshowing * 1000)){
        break;
      }
    }
  }
  move_servo(); // call this method to move the servo 180 degrees. It will check for the magma planet on its own.
}

void move_servo(){
   if (planettype == 3 && deployed == false){
    myservo.writeMicroseconds(750);
    deployed = true;
   }
}

    
void pulsar() {
  if(showstart > 0){
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
  }
}
  
// End of RGB code

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

