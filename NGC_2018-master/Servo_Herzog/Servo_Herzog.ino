#include <Servo.h>
int pos;
int planettype = 3;
Servo myservo;  // create servo object to control a servo'


void setup() {
   myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void move_servo(){
  if (planettype == 3) {
    pos = 180;
    delay (1000);
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);       // tell servo to go to position in variable 'pos'
      delay(10);
      }     
      }
}
void loop (){
move_servo();
}
