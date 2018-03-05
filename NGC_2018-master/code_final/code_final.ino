#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;
#include <Servo.h>

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

  // enable color sensing mode
  apds.enableColor(true);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //moving = false;
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
/*
    Serial.print("red: ");
    Serial.print(r);
    
    Serial.print(" green: ");
    Serial.print(g);
    
    Serial.print(" blue: ");
    Serial.print(b);
    
    Serial.print(" clear: ");
    Serial.println(c);
    Serial.println();
*/
// Values tested with Chris' phone at full brightness with colored folders

    if((g > 40) && (r < 370) && (b < 150)){ // These lines check the light values and sets a variable to a value based on the light values
      planettype = 1;
      }
    if((b > 25) && (r < 370) && (g < 165)) {
      planettype = 2;
      }
    if((r > 140) && (b < 400) && (g <165)) {
      planettype = 3;
      }
/*
   if((g > 999) && (r < 999) && (b < 999)){
      planettype = 4;
      }
    if((b > 999) && (r > 999) && (g > 999)) {
      planettype = 5;
      }
    if((r > 999) && (b > 999) && (g > 999)) {
      planettype = 6;
      }

    if((g > 800) && (r > 800) && (b > 800)) {
      plusar();
      planettype = 7;
  }
*/

// Second Version of display for the planet color

/*  switch(planettype){ //Each line will check for a different case of the variable planttype and display based on that value
    case 1:Serial.println("Green/Habitable Planet");
    case 2:Serial.println("Blue/Gas Giant");
    case 3:Serial.println("Red/Magama Planet");
    case 4:Serial.println("Yellow Planet");
    case 5:Serial.println("Magenta Planet");
    case 6:Serial.println("Cyan Planet");
	 case 7:Serial.println("Plusar with a frequency of" (F));
}
*/

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
/*    if(planettype == 4){
      Serial.println("Yellow Planet");
      }
    if(planettype == 5) {
      Serial.println("Magenta Planet");
      }
    if(planettype == 6) {
      Serial.println("Cyan Planet");
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
