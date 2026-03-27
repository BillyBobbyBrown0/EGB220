#include "arduino_secrets.h"

void setup() {
  pinMode(11, OUTPUT);
  pinMode(A5, INPUT);
}

void loop() {
  //digitalWrite(11, map(analogRead(A5), 0, 1024, 0, 255)); // analogRead(A5) max is 1024
  //map(input, 0, 1024, 0, 255);
}
