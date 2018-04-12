#include <Adafruit_NeoPixel.h>
int counter = 0;

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

void loop() {
  
  if (counter == 5)
  {
    delay(2500);
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

delay(500);

strip.setPixelColor(0, 0, 0, 0);
strip.setPixelColor(1, 0, 0, 0);
strip.setPixelColor(2, 0, 0, 0);
strip.setPixelColor(3, 0, 0, 0);
strip.setPixelColor(4, 0, 0, 0);
strip.setPixelColor(5, 0, 0, 0);
strip.setPixelColor(6, 0, 0, 0);
strip.setPixelColor(7, 0, 0, 0);

strip.show();
delay(500);
  
}
