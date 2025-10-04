//Bibliotecas
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

//Define entradas, saídas e variáveis
//Saídas
#define LED1 19
#define LED2 18
#define LED3 17
#define LED4 16
#define LED5 4
#define LED6 15

//Variáveis
char Caracter;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
}
void Liga_tudo() {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED5, HIGH);
  delay(100);
  digitalWrite(LED6, HIGH);
}

void Desliga_tudo() {
  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED2, LOW);
  delay(100);
  digitalWrite(LED3, LOW);
  delay(100);
  digitalWrite(LED4, LOW);
  delay(100);
  digitalWrite(LED5, LOW);
  delay(100);
  digitalWrite(LED6, LOW);
}

void loop() {
  Caracter = SerialBT.read();
  if (Caracter == 'A') {
    digitalWrite(LED1, HIGH);
    SerialBT.println("LED1 = LIGADO");
  }
  if (Caracter == 'a') {
    digitalWrite(LED1, LOW);
    SerialBT.println("LED1 = DESLIGADO");
  }
  if (Caracter == 'B') {
    digitalWrite(LED2, HIGH);
    SerialBT.println("LED2 = LIGADO");
  }
  if (Caracter == 'b') {
    digitalWrite(LED2, LOW);
    SerialBT.println("LED2 = DESLIGADO");
  }
  if (Caracter == 'C') {
    digitalWrite(LED3, HIGH);
    SerialBT.println("LED3 = LIGADO");
  }
  if (Caracter == 'c') {
    digitalWrite(LED3, LOW);
    SerialBT.println("LED3 = DESLIGADO");
  }
  if (Caracter == 'D') {
    digitalWrite(LED4, HIGH);
    SerialBT.println("LED4 = LIGADO");
  }
  if (Caracter == 'd') {
    digitalWrite(LED4, LOW);
    SerialBT.println("LED4 = DESLIGADO");
  }
  if (Caracter == 'E') {
    digitalWrite(LED5, HIGH);
    SerialBT.println("LED5 = LIGADO");
  }
  if (Caracter == 'e') {
    digitalWrite(LED5, LOW);
    SerialBT.println("LED5 = DESLIGADO");
  }
  if (Caracter == 'F') {
    digitalWrite(LED6, HIGH);
    SerialBT.println("LED6 = LIGADO");
  }
  if (Caracter == 'f') {
    digitalWrite(LED6, LOW);
    SerialBT.println("LED6 = DESLIGADO");
  }
  if (Caracter == 'G') {
    Liga_tudo();
    SerialBT.println("Todos os LEDs estão ligados");
  }
  if (Caracter == 'g') {
    Desliga_tudo();
    SerialBT.println("Todos os LEDs estão desligados");
  }
}