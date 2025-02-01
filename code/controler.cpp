#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;  // Using built-in Bluetooth of ESP32

#define JOYSTICK1_X 42  // ESP32 ADC pin for joystick 1 X-axis
#define JOYSTICK1_Y 38  // ESP32 ADC pin for joystick 1 Y-axis
#define JOYSTICK2_X 34  // ESP32 ADC pin for joystick 2 X-axis
#define JOYSTICK2_Y 35  // ESP32 ADC pin for joystick 2 Y-axis
#define GRIPPER_b 34  // ESP32 digital pin for gripper button
void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_Transmitter");  // Start integrated Bluetooth
    Serial.println("Integrated Bluetooth started, waiting for connection...");

    pinMode(JOYSTICK1_X, INPUT);
    pinMode(JOYSTICK1_Y, INPUT);
    pinMode(JOYSTICK2_X, INPUT);
    pinMode(JOYSTICK2_Y, INPUT);
    pinMode(GRIPPER_b, INPUT);
}

void loop() {
    int j1_x = analogRead(JOYSTICK1_X);
    int j1_y = analogRead(JOYSTICK1_Y);
    int j2_x = analogRead(JOYSTICK2_X);
    int j2_y = analogRead(JOYSTICK2_Y);
    int grip = digitalRead(GRIPPER_b);
    //Gripper controle
    if (grip == 1) {
        SerialBT.write('1');
    } else if (grip == 0) {
        SerialBT.write('2');
    }
    //servo1 controle
    if (j1_x > 3000) {
        SerialBT.write('3');
    } else if (j1_x < 1000) {
        SerialBT.write('4');
    }
    //servo2 controle
    if (j1_y > 3000) {
        SerialBT.write('5');
    } else if (j1_y < 1000) {
        SerialBT.write('6');
    }
    //servo3 controle
    if (j2_x > 3000) {
        SerialBT.write('7');
    } else if (j2_x < 1000) {
        SerialBT.write('8');
    }
    //Stepper controle
    if (j2_y > 3000) {
        SerialBT.write('9');
    } else if (j2_y < 1000) {
        SerialBT.write('10');
    }
    
    delay(50);  // Send data every 100ms
}
