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

//Entradas, Saídas e Variáveis
//Variáveis
int Valor;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
}

void loop() {
  Valor = random(0,100);
  SerialBT.println("Nível: " + String(Valor) + "%");
  delay(1000);
}