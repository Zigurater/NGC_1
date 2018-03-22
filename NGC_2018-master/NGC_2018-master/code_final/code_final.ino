#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;
#include <Servo.h>

int planettype;
int pos = 180;
int F;
int counter = 0;
unsigned long sTime1;
unsigned long sTime2;
unsigned long eTime1;
unsigned long eTime2;
unsigned long P1;
unsigned long P2;
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

// Originally values tested with Chris' phone at full brightness with colored folders
// After we received the LED strips we retested values and created ranges for each light color

    if((g <= 60 && g >= 51) && (r <= 11 && r >= 5) && (b <= 45 && b >= 36) && (c <= 100 && c >= 89)){ // These lines check the light values and sets a variable to a value based on the light values
      planettype = 1;
      }

    if((g <= 40 && g >= 28) && (r <= 10 && r >= 2) && (b <= 120 && b >= 101) && (c <= 150 && c >= 130)){
      planettype = 2;
      }
  
    if((g <= 20 && g >= 3) && (r <= 70 && r >= 52) && (b <= 20 && b >= 8) && (c <= 65 && c >= 50)){
      planettype = 3;
      }

   if((g <= 60 && g >= 51) && (r <= 60 && r >= 51) && (b <= 55 && b >= 40) && (c <= 145 && c >= 134)){
      planettype = 4;
      }

    if((g <= 40 && g >= 29) && (r <= 55 && r >= 45) && (b <= 105  && b >= 98) && (c <= 175 && c >= 163)) {
      planettype = 5;
      }

    if((g <= 71 && g >= 61) && (r <= 17 && r >= 7) && (b <= 69  && b >= 59) && (c <= 132 && c >= 122)) {
      planettype = 6;
      }

    if((g <= 92 && g >= 82) && (r <= 75 && r >= 65) && (b <= 150  && b >= 140) && (c <= 281 && c >= 271)) {
      pulsar()
      planettype = 7;
      } 


// Second Version of display for the planet color

  switch(planettype){ //Each line will check for a different case of the variable planttype and display based on that value
    case 1:
    Serial.println("Green/Habitable Planet");

    case 2:
    Serial.println("Blue/Gas Giant");

    case 3:
    Serial.println("Red/Magama Planet");

    case 4:
    Serial.println("Yellow Planet");

    case 5:
    Serial.println("Magenta Planet");

    case 6:
    Serial.println("Cyan Planet");

	 case 7:
   Serial.println("Plusar");
}

    // First version of display for the planet color
     /*if(planettype == 1){
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
*/
  delay(500);

  move_servo(); // call this method to move the servo 180 degrees. It will check for the magma planet on its own. 
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

void plusar(){
 if ((c > 1000) && (counter < 1))
      {sTime1 = millis();
      counter = counter + 1;
      }

   if ((c < 1000) && (counter == 1))
     { eTime1 = millis();
      counter = counter + 1;
         P1 = (eTime1 - sTime1) ;
      Serial.println("Period is ");
      Serial.println(P1);
      Serial.println(eTime1);
      Serial.println(sTime1);
     }
     // 
   if ((c > 1000) && (counter == 2))
      {sTime2 = millis();
      counter = counter + 1;
      }

   if ((c < 1000) && (counter == 3))
     { eTime2 = millis();
      counter = counter + 1;
         P2 = (eTime2 - sTime2) ;
      Serial.println("Period is ");
      Serial.println(P2);
      Serial.println(eTime2);
      Serial.println(sTime2);
     }
}
