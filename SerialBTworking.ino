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
int ledPins[16] = {13, 12, 14, 27, 26, 25, 33, 32, 16, 17, 5, 18, 19, 21, 22, 23}; //pin numbers that control leds
int joystickVals[16]; 

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
    
  for(int i=0; i<16; i++){
    pinMode(ledPins[i], OUTPUT);
  }
}


void updateInputs(){
  joystickVals[0] = SerialBT.read();
  joystickVals[1] = SerialBT.read();
  joystickVals[2] = SerialBT.read();
  joystickVals[3] = SerialBT.read();
  joystickVals[4] = SerialBT.read();
  joystickVals[5] = SerialBT.read();
  joystickVals[6] = SerialBT.read();
  joystickVals[7] = SerialBT.read();
  joystickVals[8] = SerialBT.read();
  joystickVals[9] = SerialBT.read();
  joystickVals[10] = SerialBT.read();
  joystickVals[11] = SerialBT.read();
  joystickVals[12] = SerialBT.read();
  joystickVals[13] = SerialBT.read();
  joystickVals[14] = SerialBT.read();
  joystickVals[15] = SerialBT.read();
}

void printInputs(){
  Serial.print("val[0]:  ");Serial.print(joystickVals[0]);Serial.print(" ");
  Serial.print("val[1]:  ");Serial.print(joystickVals[1]);Serial.print(" ");
  Serial.print("val[2]:  ");Serial.print(joystickVals[2]);Serial.print(" ");
  Serial.print("val[3]:  ");Serial.print(joystickVals[3]);Serial.print(" ");
  Serial.print("val[4]:  ");Serial.print(joystickVals[4]);Serial.print(" ");
  Serial.print("val[5]:  ");Serial.print(joystickVals[5]);Serial.print(" ");
  Serial.print("val[6]:  ");Serial.print(joystickVals[6]);Serial.print(" ");
  Serial.print("val[7]:  ");Serial.print(joystickVals[7]);Serial.print(" ");
  Serial.print("val[8]:  ");Serial.print(joystickVals[8]);Serial.print(" ");
  Serial.print("val[9]:  ");Serial.print(joystickVals[9]);Serial.print(" ");
  Serial.print("val[10]:  ");Serial.print(joystickVals[10]);Serial.print(" ");
  Serial.print("val[11]:  ");Serial.print(joystickVals[11]);Serial.print(" ");
  Serial.print("val[12]:  ");Serial.print(joystickVals[12]);Serial.print(" ");
  Serial.print("val[13]:  ");Serial.print(joystickVals[13]);Serial.print(" ");
  Serial.print("val[14]:  ");Serial.print(joystickVals[14]);Serial.print(" ");
  Serial.print("val[15]:  ");Serial.println(joystickVals[15]);
}

void controlLeds(){
  for(int i=0; i<16; i++){
      if(i<=5){
        analogWrite(ledPins[i], map(joystickVals[i], 0, 200, 0, 255));
      }else{
        digitalWrite(ledPins[i], joystickVals[i]);
      }
    }
}
  

void loop() {
  if(SerialBT.available()) {
    updateInputs();
    printInputs();
    controlLeds();
  }
  delay(5);
}
