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

//Define Entradas, Saídas e Variáveis
//Saídas
#define LuzFrente 19
#define LuzFundo 18
#define VentiladorFundo 17
#define VentiladorLateral 16

//Variáveis
char Caracter;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  pinMode(LuzFrente, OUTPUT);
  pinMode(LuzFundo, OUTPUT);
  pinMode(VentiladorFundo, OUTPUT);
  pinMode(VentiladorLateral, OUTPUT);
}

void TodasLuzesLigadas() {
  digitalWrite(LuzFrente, HIGH);
  digitalWrite(LuzFundo, HIGH);
  SerialBT.println("TODAS AS LUZES ESTÃO LIGADAS");
}

void TodasLuzesDesligadas() {
  digitalWrite(LuzFrente, LOW);
  digitalWrite(LuzFundo, LOW);
  SerialBT.println("TODAS AS LUZES ESTÃO DESLIGADAS");
}

void VentiladoresLigados() {
  digitalWrite(VentiladorFundo, HIGH);
  digitalWrite(VentiladorLateral, HIGH);
  SerialBT.println("TODOS OS VENTILADORES ESTÃO LIGADOS");
}

void VentiladoresDesligados() {
  digitalWrite(VentiladorFundo, LOW);
  digitalWrite(VentiladorLateral, LOW);
  SerialBT.println("TODOS OS VENTILADORES ESTÃO DESLIGADOS");
}

void TudoLigado() {
  TodasLuzesLigadas();
  VentiladoresLigados();
}

void TudoDesligado() {
  TodasLuzesDesligadas();
  VentiladoresDesligados();
}

void loop() {
  Caracter = SerialBT.read();
  if (Caracter == 'A') {
    digitalWrite(LuzFrente, HIGH);
    SerialBT.println("LUZES DA FRENTE = LIGADAS");
  }
  if (Caracter == 'a') {
    digitalWrite(LuzFrente, LOW);
    SerialBT.println("LUZES DA FRENTE = DESLIGADAS");
  }
  if (Caracter == 'B') {
    digitalWrite(LuzFundo, HIGH);
    SerialBT.println("LUZES DO FUNDO = LIGADAS");
  }
  if (Caracter == 'b') {
    digitalWrite(LuzFundo, LOW);
    SerialBT.println("LUZES DO FUNDO = DESLIGADAS");
  }
  if (Caracter == 'C') {
    digitalWrite(VentiladorFundo, HIGH);
    SerialBT.println("VENTILADOR DO FUNDO = LIGADO");
  }
  if (Caracter == 'c') {
    digitalWrite(VentiladorFundo, LOW);
    SerialBT.println("VENTILADOR DO FUNDO = DESLIGADO");
  }
  if (Caracter == 'D') {
    digitalWrite(VentiladorLateral, HIGH);
    SerialBT.println("VENTILADOR DA LATERAL = LIGADO");
  }
  if (Caracter == 'd') {
    digitalWrite(VentiladorLateral, LOW);
    SerialBT.println("VENTILADOR DA LATERAL = DESLIGADO");
  }
  if (Caracter == 'E') {
    TodasLuzesLigadas();
  }
  if (Caracter == 'e') {
    TodasLuzesDesligadas();
  }
  if (Caracter == 'F') {
    VentiladoresLigados();
  }
  if (Caracter == 'f') {
    VentiladoresDesligados();
  }
  if (Caracter == 'G') {
    TudoLigado();
  }
  if (Caracter == 'g') {
    TudoDesligado();
  }
}