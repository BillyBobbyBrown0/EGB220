// -------- Motor Pin Definitions --------
const int motorA_dir = 8;   // PB0
const int motorA_pwm = 13;  // PB7 (OC0A)

//const int motorB_dir = 7;   // PE6
//const int motorB_pwm = 5;   // PD0 (OC0B)

int maxValue = 255;   // PWM speed (0-255)
int minValue = 85;
int avgValue = 170;

void setup() {

  pinMode(motorA_dir, OUTPUT);
  pinMode(motorA_pwm, OUTPUT);

  //pinMode(motorB_dir, OUTPUT);
  //pinMode(motorB_pwm, OUTPUT);
}

void loop() {

  // -------- Move Forward --------
  digitalWrite(motorA_dir, HIGH);
  //digitalWrite(motorB_dir, HIGH);

  analogWrite(motorA_pwm, maxValue);
  //analogWrite(motorB_pwm, maxValue);

  delay(3000);

  // -------- Move Backward --------
  digitalWrite(motorA_dir, LOW);
  //digitalWrite(motorB_dir, LOW);

  analogWrite(motorA_pwm, maxValue);
  //analogWrite(motorB_pwm, maxValue);

  delay(3000);

  // -------- Stop --------
  analogWrite(motorA_pwm, 0);
  //analogWrite(motorB_pwm, 0);

  delay(3000);
}