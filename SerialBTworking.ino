//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include <Arduino.h>
#include "BluetoothSerial.h"

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234"; // Change this to more secure PIN.

String device_name = "SwerveBotDevKit";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
int led = 4;
int joystickVals[4];
byte data;
void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif

  pinMode(led, OUTPUT);

}

void loop() {
  // if (Serial.available()) {
  //   SerialBT.write(Serial.read());
  // }
  if(SerialBT.available()) {

    joystickVals[0] = SerialBT.read();
    joystickVals[1] = SerialBT.read();
    joystickVals[2] = SerialBT.read();
    joystickVals[3] = SerialBT.read();
    //Serial.println(data);//0 becomes 48, one becomes 49
    Serial.print("val[0]:  ");Serial.print(joystickVals[0]);Serial.print(" ");
    Serial.print("val[1]:  ");Serial.print(joystickVals[1]);Serial.print(" ");
    Serial.print("val[2]:  ");Serial.print(joystickVals[2]);Serial.print(" ");
    Serial.print("val[3]:  ");Serial.println(joystickVals[3]);

    // digitalWrite(led, data-48);
    
  }

  // // Serial.write(SerialBT.read());
  // delay(5);
}
