#include <WiFi.h>
#include <PubSubClient.h>
#include "EmonLib.h"
#include <DHT11.h>
EnergyMonitor emon1;
DHT11 dht11(23);

// Update these with values suitable for your network.

const char* ssid = "WI-FI EDUC";
const char* password = "ac5ce0ss7@educ";
const char* mqtt_server = "10.87.47.18";

//Variáveis para o ESP32 receber dados
String my_payload;
String my_topic;

//Variáveis do ESP32
float corrente;
float temperature;
float humidity;

WiFiClient ESP_Gustavo;
PubSubClient client(ESP_Gustavo);


void setup_wifi() {

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String conc_payload;
  for (int i = 0; i < length; i++) {
    conc_payload += ((char)payload[i]);
  }
  my_payload = conc_payload;
  my_topic = topic;

}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP_Gustavo")) {
      Serial.println("connected");
      client.subscribe("TOP_Gustavo");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(34, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  emon1.current(34, 20);
}

void controle(){
  //A
  if (my_payload == "A") {
  digitalWrite(19, HIGH);
  client.publish("StatusC371",String("Ligado").c_str());
  Serial.println("Ligado");
  }
  if (my_payload == "a") {
  digitalWrite(19, LOW);
  client.publish("StatusC371",String("Desligado").c_str());
  Serial.println("Desligado");
  }
  //B
  if (my_payload == "B") {
  digitalWrite(18, HIGH);
  client.publish("StatusC372",String("Ligado").c_str());
  Serial.println("Ligado");
  }
  if (my_payload == "b") {
  digitalWrite(18, LOW);
  client.publish("StatusC372",String("Desligado").c_str());
  Serial.println("Desligado");
  }
  //C
  if (my_payload == "C") {
  digitalWrite(17, HIGH);
  client.publish("StatusC373",String("Ligado").c_str());
  Serial.println("Ligado");
  }
  if (my_payload == "c") {
  digitalWrite(17, LOW);
  client.publish("StatusC373",String("Desligado").c_str());
  Serial.println("Desligado");
  }
  //D
  if (my_payload == "D") {
  digitalWrite(16, HIGH);
  client.publish("StatusC374",String("Ligado").c_str());
  Serial.println("Ligado");
  }
  if (my_payload == "d") {
  digitalWrite(16, LOW);
  client.publish("StatusC374",String("Desligado").c_str());
  Serial.println("Desligado");
  }
}

void LeitorCorrente(){
  corrente = emon1.calcIrms(1480);
  client.publish("CORRENTE_SALA",String(corrente).c_str());
  delay(1000);
}

void LeituraTempHumidty(){
  temperature = dht11.readTemperature();
  humidity = dht11.readHumidity();
  client.publish("temperatura",String(temperature).c_str());
  client.publish("umidade",String(humidity).c_str());
}

void IpMacAddress(){
  String IpAddress = String(WiFi.localIP());
  client.publish("IP_SALA",String(IpAddress).c_str());
  String MacAddress = String(WiFi.macAddress());
  client.publish("MAC_SALA",String(MacAddress).c_str());
}

void Conexao(){
  if (WiFi.status()) {
  digitalWrite(2, HIGH);
  }else {
  digitalWrite(2, LOW);
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  Conexao();
  controle();
  IpMacAddress();
  LeitorCorrente();
  LeituraTempHumidty();
}