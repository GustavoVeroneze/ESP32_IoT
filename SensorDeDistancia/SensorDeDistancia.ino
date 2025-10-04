#include <Ultrasonic.h>

Ultrasonic ultrasonic(32, 35);
int distance;

#include "BluetoothSerial.h"

String device_name = "ESP32_Gustavo";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

#define LED1 19

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  pinMode(LED1, OUTPUT);
}

void loop() {
  distance = ultrasonic.read();
  
  if(distance <= 10){
    digitalWrite(LED1, HIGH);
    SerialBT.println("Cuidado, objeto em " + String(distance) + "cm");
  }
  if(distance > 10){
    digitalWrite(LED1, LOW);
  }
  delay(1000);
}
