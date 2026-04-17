#include <Arduino.h>

#define n_sens 10

// Sensor mapping (your board)
uint8_t sens[n_sens] = {
  4, 5, 6, 7,
  11, 10, 9, 8,
  0, 1
};

uint16_t sens_out[n_sens];

// Threshold
int threshold = 150;

// Motor speeds
int maxValue = 255;
int minValue = 85;
int baseSpeed = 170;

// Motor pins
#define MOTOR_B_PWM 3
#define MOTOR_B_DIR 7

#define MOTOR_A_PWM 11
#define MOTOR_A_DIR 17

// Track last direction (for recovery)
int lastError = 0;

// Check black
bool isBlack(uint16_t val) {
  return val < threshold;
}

// ADC read
uint16_t readADC(uint8_t ch) {

  if (ch < 8) {
    ADCSRB &= ~(1 << MUX5);
  } else {
    ADCSRB |= (1 << MUX5);
    ch -= 8;
  }

  ADMUX = (1 << REFS0) | (ch & 0x07);

  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));

  return ADC;
}

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(MOTOR_B_PWM, OUTPUT);
  pinMode(MOTOR_B_DIR, OUTPUT);

  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(MOTOR_A_DIR, OUTPUT);

  digitalWrite(MOTOR_A_DIR, HIGH);
  digitalWrite(MOTOR_B_DIR, HIGH);

  // ADC setup
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN)
         | (1 << ADPS2)
         | (1 << ADPS1)
         | (1 << ADPS0);
  ADCSRB = 0;

  Serial.println("=== LINE FOLLOWER READY ===");
}

void loop() {

  // Read sensors
  for (int i = 0; i < n_sens; i++) {
    sens_out[i] = readADC(sens[i]);
  }

  // ---- Calculate error ----
  int error = 0;
  int weightSum = 0;

  // Stronger edge weights (better turning)
  int weights[n_sens] = {-8,-6,-4,-2,-1,1,2,4,6,8};

  for (int i = 0; i < n_sens; i++) {
    if (isBlack(sens_out[i])) {
      error += weights[i];
      weightSum++;
    }
  }

  // ---- Line lost handling ----
if (weightSum == 0) {
  // Go straight slowly instead of committing to a turn
  analogWrite(MOTOR_A_PWM, baseSpeed);
  analogWrite(MOTOR_B_PWM, baseSpeed);
  return;
}

  // Average error
  error = error / weightSum;

  // ---- Strong correction ----
  int correction = error * 25;


  // Motor speeds
  int leftSpeed  = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  // Clamp speeds
  leftSpeed  = constrain(leftSpeed, minValue, maxValue);
  rightSpeed = constrain(rightSpeed, minValue, maxValue);

  // Apply speeds
  analogWrite(MOTOR_A_PWM, leftSpeed);
  analogWrite(MOTOR_B_PWM, rightSpeed);

  // ---- Debug ----
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print(" L:");
  Serial.print(leftSpeed);
  Serial.print(" R:");
  Serial.println(rightSpeed);

  delay(30);
}
