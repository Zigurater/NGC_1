

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(115200);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
}

void loop() {
  //create some variables to store the color data in
  uint16_t r, g, b, c;
  
  //wait for color data to be ready
  while(!apds.colorDataReady()){
    delay(5);
  }

  //get the data and print the different channels
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

  /*
  if(g > 200){
    do {
      Serial.println("Green");
    }
    while (b<155 or r < 400);
  }
   
  if(b > 155){
    do{
    Serial.println("Blue");
    }
    while(g< 200 or r < 400);
      
  }

  if(r > 400){
    do{
       Serial.println("Red");
    }
    while (g< 200 or b < 155);
    
  }
    


*/
  delay(300);
  
}
