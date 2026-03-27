#include "arduino_secrets.h"

#include<Arduino.h>
#include <Servo.h>

Servo S1;

//THIS WILL ALL BE ON THE TINSEY as the servo is mounted on the tinsey
void setup() {
  pinMode(9, OUTPUT);
  S1.attach(9);

}

void loop() {
  S1.write(255); //This will go to the maximum

}
