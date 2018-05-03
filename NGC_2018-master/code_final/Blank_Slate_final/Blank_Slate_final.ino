#include "Adafruit_APDS9960.h"
#include <Adafruit_NeoPixel.h>
Adafruit_APDS9960 apds;
#include <Servo.h>
#define PIN            4
#define NUMPIXELS      8
#define INT_PIN 3
bool get_frequency = false;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//pulsar variables (this code concept comes from "Pulsar_test_code.ino" in the "color strip test" folder)
int Hz;
int LswitchR;
int LswitchL;
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
bool deployed = false;

void setup() {
  Serial.begin(115200);
  pinMode(INT_PIN, INPUT_PULLUP);
  if (!apds.begin()) {
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");
  strip.begin(); // This initializes the NeoPixel library.
  // enable color sensing mode
  apds.enableColor(true);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pos = 200;
  
  myservo.writeMicroseconds(2250);
  apds.enableProximity(true);
  strip.show();
  pinMode(10, INPUT); //left limit switch
  pinMode(7, INPUT); //Right limit switch
}
void loop() {
  // create some variables to store the color data in
  uint16_t r, g, b, c;
  // wait for color data to be ready
  while (!apds.colorDataReady()) {
    delay(5);
  }
  // get the data and print the different channels
  //proximity = apds.readProximity;
  Serial.println("proximity: ");
  Serial.println(apds.readProximity());
   LswitchR = digitalRead(10);
  LswitchL = digitalRead(7);
  if ((LswitchR== HIGH) or (LswitchL == HIGH))  {
    wormhole = true;
  }

  else if (((LswitchR== LOW) or (LswitchL == LOW)) ) {
    wormhole = false;
    delay(1000); // This delay prevents the buttons from retriggering sensing data when leaving the wormhole
  }
  if(apds.readProximity() > 5)
  {
    delay(5000); //This delay prevents the case from being switched when leaving the wormhole when the limit switches are still depressed
  }
  if (wormhole == true) {
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

     if ((c>150)) { //pulsar
      planettype = 7;
      //new values(46,59,77,175)
    }
    else if ((g> b) && (b>r) &&  (c < 115)) { //green
      planettype = 6;
      //(8,68,42,109)
      //New Values from sunday (16,57,35,106)
    }

    else if ((b>g) && (g>r)) { //blue
      planettype = 2;
      //(3,35,110,141)
      //new values (11,30,84,123)
    }

    else if ((r>b)&&(b>g)) { //red
      planettype = 3;
      //(43,3,7,44)
      //new values from sunday(39,6,8,42)
    }

    else if ((b<g)&&(b<r)) { //yellow
      planettype = 4;
      //(57,68,48,157)
      //new values(49,48,33,123)
    }

    else if ((b>r)&&(r>g)) { //magenta
      planettype = 5;
      //(51,36,111,184)
      //new values(46,28,71,136)
      
    }

    else if (((g> b) && (b>r) &&  (c >= 115))) { //cyan
      planettype = 1;
      //(7,70,66,131)
      //(19,56,49,120)
    }

    
   
  //}
  // Second Version of display for the planet color

  switch (planettype) { //Each line will check for a different case of the variable planttype and display based on that value
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
      strip.setPixelColor(0, 0, 0 , 0);
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
      //I have left this blank. we need to come up with a new way of determining the period, when inside the wormhole in the off period
      // the case is switched to blue. possibly use a function to determine the period using do while loops and the conditional is
      // if the "c" value is low
      // what i was thinking, pulsar flash is something that will be returned at the end of the function once the led has flashed
      // the idea of this loop is to run itself after it has discovered a pulsar initially and then to run itself repeatedly until it has finihsed flashing
      /* 
      
            do while (pulsar_flash == false)
                this part would be the function(
               1 determine the frequency using something similar to what we did before
               2 determine a delay time for that frequency
               3 flash for x amount of times
               4 pulsar_flash = true) end of function
               
             
            loop
 
            */
      }
    }
  move_servo(); // call this method to move the servo 180 degrees. It will check for the magma planet on its own.
  }

void move_servo() {
  if (planettype == 3 && deployed == false) {
    myservo.writeMicroseconds(750);
    deployed = true;
  }
}


/*void pulsar() {
  if (showstart > 0) {
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
}*/



