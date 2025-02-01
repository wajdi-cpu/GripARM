#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
#include <Stepper.h>

int speed_Rev = 200;
int motorSpeed = 300;
Stepper stepper(speed_Rev, 8, 9, 10, 11);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
SoftwareSerial BTSerial(2, 3); // RX, TX

#define SERVO_MIN  150  // Minimum pulse length
#define SERVO_MAX  600  // Maximum pulse length

// Initialize servo positions
int pos2 = SERVO_MIN;
int pos3 = SERVO_MIN;
int pos4 = SERVO_MIN;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Set frequency to 50Hz for servos
  BTSerial.begin(9600);
  stepper.setSpeed(motorSpeed);
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    Serial.print("Received Command: ");
    Serial.println(command);
    
    switch (command) {
      // Move gripper-servo  
      case '1':
        pwm.setPWM(0, 0, SERVO_MAX );
        break;
      case '2':
        pwm.setPWM(0, 0, SERVO_MIN );
        break;

      // Move servo1
      case '3':
        if (pos2 >= SERVO_MIN && pos2 < SERVO_MAX) {
          pos2 += 10;
          pwm.setPWM(1, 0, pos2);
        }
        break;
      case '4':
        if (pos2 > SERVO_MIN && pos2 <= SERVO_MAX) {
          pos2 -= 10;
          pwm.setPWM(1, 0, pos2);
        }
        break;

      // Move servo2
      case '5':
        if (pos3 >= SERVO_MIN && pos3 < SERVO_MAX) {
          pos3 += 10;
          pwm.setPWM(2, 0, pos3);
        }
        break;
      case '6':
        if (pos3 > SERVO_MIN && pos3 <= SERVO_MAX) {
          pos3 -= 10;
          pwm.setPWM(2, 0, pos3);
        }
        break;

      // Move servo3
      case '7':
        if (pos4 >= SERVO_MIN && pos4 < SERVO_MAX) {
          pos4 += 10;
          pwm.setPWM(3, 0, pos4);
        }
        break;
      case '8':
        if (pos4 > SERVO_MIN && pos4 <= SERVO_MAX) {
          pos4 -= 10;
          pwm.setPWM(3, 0, pos4);
        }
        break;

      // Move Stepper
      case '9':
        stepper.step(speed_Rev);
        break;
      case '10': 
        stepper.step(-speed_Rev);
        break;

      default:
        Serial.println("Unknown command");
        break;
    }
  }
}
