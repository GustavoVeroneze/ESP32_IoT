// Bibliotecas
#include <WiFi.h> 
#include <PubSubClient.h>  

// Credenciais de conexão WiFi e Broker
const char* ssid = "ssid";         // Nome da rede Wi-Fi à qual o ESP32 irá se conectar
const char* password = "password";  // Senha da rede Wi-Fi
const char* mqtt_server = "your ip"; // Endereço IP do broker MQTT

// Nome do Cliente
WiFiClient ESP32_GUSTAVO;              // Objeto que representa a conexão Wi-Fi
PubSubClient client(ESP32_GUSTAVO);    // Objeto cliente MQTT que irá usar a conexão Wi-Fi para se comunicar com o broker

int entrou = 0;
int saiu = 0;
int producao = 0;

void setup_wifi() {
  Serial.print("Connecting to ");      // Exibe no terminal o processo de conexão
  Serial.println(ssid);                 // Imprime o nome da rede Wi-Fi que está sendo acessada

  WiFi.mode(WIFI_STA);                  // Configura o ESP32 para o modo Station (se conecta a uma rede Wi-Fi)
  WiFi.begin(ssid, password);           // Inicia a conexão com a rede Wi-Fi utilizando o SSID e a senha fornecidos

  // Aguarda até que a conexão Wi-Fi seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);                         // Espera 500ms entre as tentativas de conexão
    Serial.print(".");                  // Exibe um ponto (.) a cada tentativa para mostrar que o código está tentando se conectar
  }

  // Após a conexão ser estabelecida
  Serial.println("WiFi connected");     // Informa no terminal que a conexão foi bem-sucedida
  Serial.print("IP address: ");       // Exibe o endereço IP atribuído ao ESP32
  Serial.println(WiFi.localIP());       // Imprime o IP local atribuído ao ESP32 pela rede Wi-Fi
  Serial.print("MAC-Address:");         // Exibe a mensagem "MAC-Address:" no terminal
  Serial.println(WiFi.macAddress());    // Exibe o endereço MAC do ESP32 na rede Wi-Fi
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP32_GUSTAVO")) {
      Serial.println("connected");
      client.subscribe("TOP_GUSTAVO");
    } else {
      Serial.print("failed, rc=");
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(33, INPUT);
  pinMode(25, INPUT);
  pinMode(2, OUTPUT);  // Pino de conexão Wi-Fi
  setup_wifi();                           // Chama a função que conecta o ESP32 à rede Wi-Fi
  client.setServer(mqtt_server, 1883);    // Define o endereço IP e a porta (1883) do broker MQTT
}

void conexao() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(2, HIGH);  // Indica que o Wi-Fi está conectado
  } else {
    digitalWrite(2, LOW);   // Indica que o Wi-Fi não está conectado
  }
}

void linha() {
  if (digitalRead(33) == LOW) {
  entrou = entrou +1;
  producao = entrou - saiu;
  client.publish("ENTRADA", String(entrou).c_str());
  client.publish("PRODUCAO", String(producao).c_str());
  delay(300);
  }

  if(digitalRead(25) == LOW) {
  saiu = saiu +1;
  producao = entrou - saiu;
  client.publish("SAIDA", String(saiu).c_str());
  client.publish("PRODUCAO", String(producao).c_str());
  delay(300);
  }
}

void IpMacAddress(){
  String IpAddress = String(WiFi.localIP());
  client.publish("IP_LINHA",String(IpAddress).c_str());
  String MacAddress = String(WiFi.macAddress());
  client.publish("MAC_LINHA",String(MacAddress).c_str());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  conexao();
  linha();
  IpMacAddress();
}
