//inclusão das bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>
#include "EmonLib.h"
EnergyMonitor emon1; 

//Variáveis para receber os dados
String my_payload;
String my_topic;
//Variáveis para o EPS enviar dados
float Corrente;

//configurações para acessar a REDE e o broker MQTT
const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "your ip";

//nome do controlador
WiFiClient Oficina_Gustavo;
PubSubClient client(Oficina_Gustavo);

//Função para o ESP32 se conectar na internet
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

//Função para o ESP32 receber dados
void callback(char* topic, byte* payload, unsigned int length) {
  String conc_payload;
  for (int i = 0; i < length; i++) {
    conc_payload += ((char)payload[i]);
  }
  my_payload = conc_payload;
  my_topic = topic;
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("Oficina_Gustavo")) {
      Serial.println("connected");
      client.subscribe("TOP_Gustavo_OFC");
    } else {
      Serial.print("failed, rc=");
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(2,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(16,OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  emon1.current(1, 111.1);
}

void conexao(){
  if(WiFi.status()){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
}

//função onde o ESP32 recebe dados
void ESP32_RECEBE(){

  //A
  if(my_payload == "A"){
    digitalWrite(19, HIGH);
    client.publish("C1_Gustavo_OFC",String("LIGADO").c_str());
  }
  if(my_payload == "a"){
    digitalWrite(19, LOW);
    client.publish("C1_Gustavo_OFC",String("DESLIGADO").c_str());
  }

  //B
  if(my_payload == "B"){
    digitalWrite(18, HIGH);
    client.publish("C2_Gustavo_OFC",String("LIGADO").c_str());
  }
  if(my_payload == "b"){
    digitalWrite(18, LOW);
    client.publish("C2_Gustavo_OFC",String("DESLIGADO").c_str());
  }

  //C
  if(my_payload == "C"){
    digitalWrite(17, HIGH);
    client.publish("Morsa_Gustavo_OFC",String("LIGADO").c_str());
  }
  if(my_payload == "c"){
    digitalWrite(17, LOW);
    client.publish("Morsa_Gustavo_OFC",String("DESLIGADO").c_str());
  }

  //D
  if(my_payload == "D"){
    digitalWrite(16, HIGH);
    client.publish("Bancada_Gustavo_OFC",String("LIGADO").c_str());
  }
  if(my_payload == "d"){
    digitalWrite(16, LOW);
    client.publish("Bancada_Gustavo_OFC",String("DESLIGADO").c_str());
  }

}

void Monitor_Corrente(){
  Corrente = emon1.calcIrms(1480);
  client.publish("Corrente_Gustavo_OFC",String(Corrente).c_str());
  delay(200);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  conexao();
  ESP32_RECEBE();

}
