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

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

int planettype;
int F;
bool moving;
bool pulsar_value;

void setup() {
      Serial.begin(115200);
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  // enable color sensing mode
  apds.enableColor(true);
  moving = false;
  pulsar_value = wait_for_on;
}


void plusar(){
  while (!moving){
    if (planettype == 7){
    wait_for_on()
    }
    if (pulsar_value){
      //write time value to something
      wait_for_off()
    }
    if (moving){
      break;
    }
    }
    }