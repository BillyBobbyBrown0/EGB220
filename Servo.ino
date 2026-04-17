#include<Arduino.h>
#include <Servo.h>

Servo S1;
Servo S2;

//THIS WILL ALL BE ON THE TINSEY as the servo is mounted on the tinsey
void setup() {
  S1.attach(9);   // First servo on pin 9
  S2.attach(10);  // Second servo on pin 10

}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    S1.write(angle);
    S2.write(180-angle); // opposite direction
    delay(20);
  }
}
