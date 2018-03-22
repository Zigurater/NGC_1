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
double F= 1.5;
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
  //pulsar_value = wait_for_on
}
void loop() {
  /*if (){
    moving = true
  }
  */
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
    if((g > 320) && (r > 335) && (b > 255)&& (c > 935)) {
      //plusar();
      planettype = 7;
  }


// Second Version of display for the planet color

/*  switch(planettype){ //Each line will check for a different case of the variable planttype and display based on that value
    case 1:Serial.println("Green/Habitable Planet");
    case 2:Serial.println("Blue/Gas Giant");
    case 3:Serial.println("Red/Magama Planet");
    case 4:Serial.println("Yellow Planet");
    case 5:Serial.println("Magenta Planet");
    case 6:Serial.println("Cyan Planet");
    case 7:Serial.println("Plusar with a frequency of" F)
}
*/
if( planettype == 7){
  Serial.println("Pulsar of Frequency");
  Serial.println(F);
}


  delay(500);
}
// End of RGB code


/*
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
    */
