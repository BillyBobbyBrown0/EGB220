#include <Arduino.h>
#include <Encoder.h>

#define ENCODER_PIN_A 0
#define ENCODER_PIN_B 1

#define COUNTS_PER_ROTATION (12*50)

const double kp = 5.0;
const double ki = 1.0;
const double kd = 4.0;
double target_speed = 0.1;

Encoder encoder_A(ENCODER_PIN_A, ENCODER_PIN_B);

// PWM speed (0-255)
int maxValue = 255; 
int minValue = 85;
int avgValue = 170;

void setup() {
  //Encoder Pin
  pinMode(9, OUTPUT);


  //THIS IS ON MOTOR B 
  //pinMode(3, OUTPUT);
  //pinMode(7, OUTPUT);

  //THIS IS MOTOR A
  pinMode(11, OUTPUT); // This is PE6
  pinMode(17, OUTPUT); // This is the Direction of the motor 
  //digitalWrite(17, HIGH); This can go in the loop
}

void loop() {
  static unsigned long previous_time = micros();
  static double previous_position = 0.0;
  static double previous_ep = 0.0;
  static double pwm_control = 0.0;
  static double ei = 0.0;

  unsigned long current_time = micros();
  unsigned long dt_us = current_time - previous_time;
  double dt_s = double(dt_us) / 1000000;

  double current_position = encoder_A.read() / COUNTS_PER_ROTATION;
  double dp = current_position - previous_position;

  double current_speed = dp / dt_s;

  double ep = target_speed - current_speed;
  double ed = (ep - previous_ep) * dt_s;
  ei += (ep * dt_s);
  ei = constrain(ei, -10.0, 10.0); // Dont change will produce latency better to only make smaller

  pwm_control += (ep * kp) + (ei * ki) + (ed * kd);
  pwm_control = constrain(pwm_control, 0, 255);

  analogWrite(11, uint8_t(pwm_control));


  previous_position = current_position;
  previous_time = current_time;
  previous_ep = ep;

  //THIS IS FOR MOTOR B
  //digitalWrite(7, HIGH); //This is in the loop so conditions can be applied
  //analogWrite(3, maxValue); //This turns on the B motor (M1) and also can control the speed (Changing the value between 0-255 will change the speed)
  
  //analogWrite(11, avgValue); //This is on M2

  
  
}