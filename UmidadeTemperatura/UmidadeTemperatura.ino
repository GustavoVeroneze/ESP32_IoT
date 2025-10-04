#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT11.h>
DHT11 dht11(23);

const char* ssid = "WI-FI EDUC";
const char* password = "ac5ce0ss7@educ";
const char* mqtt_server = "10.87.47.28";

WiFiClient ESP_GUSTAVO;
PubSubClient client(ESP_GUSTAVO);

void setup_wifi() {

  Serial.println();
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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP_GUSTAVO")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void conexao(){
  if(WiFi.status()){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
}

void DHT11() {
  float temperatura = dht11.readTemperature();
  float umidade = dht11.readHumidity();

  client.publish("TEMP_GUSTAVO", String(temperatura).c_str());
  client.publish("UMID_GUSTAVO", String(umidade).c_str());

  delay(1000);
}

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  conexao();
  DHT11();

}
