#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;



int counter = 0;
unsigned long sTime1;
unsigned long sTime2;
unsigned long eTime1;
unsigned long eTime2;
unsigned long P1;
unsigned long P2;

void setup() {
    Serial.begin(115200);
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  // enable color sensing mode
  apds.enableColor(true);
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

 /*   Serial.print("red: ");
    Serial.print(r);
    
    Serial.print(" green: ");
    Serial.print(g);
    
    Serial.print(" blue: ");
    Serial.print(b);
    
   
    Serial.print(" clear: ");
    Serial.println(c);
    Serial.println();
*/
   if ((c > 100) && (counter < 1)){
    counter = counter + 1;
      // sTime1 = millis(); 
   }

   if ((c < 100) && (counter == 1)){
    counter = counter + 1;
   /* eTime1 = millis();
      P1 = (eTime1 - sTime1);
      Serial.println("Period is ");
      Serial.println(P1);
      Serial.println(eTime1);
      Serial.println(sTime1);
   */
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
      
}
