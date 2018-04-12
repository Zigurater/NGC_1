#include <Adafruit_NeoPixel.h>
int counter = 0;
int dRate= 1000;
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 6, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
//Parameter 1  = number of pixels in strip
//Parameter 2 = pin number (most are valid)
//Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

}


//Declare desired frequency:
int Hz = 1;


/*if (Hz == 0.5) {
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

*/
void loop() {
  
  if (counter == 5)
  {
    delay(5 * dRate);
  counter=0;
  }
  
    // put your main code here, to run repeatedly:
  strip.setPixelColor(0, 255, 255, 255);
  strip.setPixelColor(1, 255, 255, 255);
  strip.setPixelColor(2, 255, 255, 255);
  strip.setPixelColor(3, 255, 255, 255);
  strip.setPixelColor(4, 255, 255, 255);
  strip.setPixelColor(5, 255, 255, 255);
  strip.setPixelColor(6, 255, 255, 255);
  strip.setPixelColor(7, 255, 255, 255);
  counter+= 1;
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
