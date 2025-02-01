#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN  150  // Minimum pulse length
#define SERVO_MAX  600  // Maximum pulse length

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Set frequency to 50Hz for servos
}

void loop() {
  // Move both servos from min to max
  for (int pos = SERVO_MIN; pos < SERVO_MAX; pos += 10) {
    pwm.setPWM(0, 0, pos);  // Servo on channel 0
    pwm.setPWM(1, 0, pos);  // Servo on channel 1
    pwm.setPWM(2, 0, pos);
    pwm.setPWM(3, 0, pos);
  }
  // Move back
}

