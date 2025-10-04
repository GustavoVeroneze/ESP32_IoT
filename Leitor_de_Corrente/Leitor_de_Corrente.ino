//Bibliotecas
#include <WiFi.h>                // Inclui a biblioteca WiFi para permitir a conexão com redes Wi-Fi
#include <PubSubClient.h>        // Inclui a biblioteca PubSubClient para comunicação MQTT
#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

//Credenciais de conexão WiFi e Broker
const char* ssid = "ssid";         // Nome da rede Wi-Fi à qual o ESP32 irá se conectar
const char* password = "password";  // Senha da rede Wi-Fi
const char* mqtt_server = "your ip"; // Endereço IP do broker MQTT

//Nome do Cliente
WiFiClient ESP32_GUSTAVO;              // Objeto que representa a conexão Wi-Fi
PubSubClient client(ESP32_GUSTAVO);    // Objeto cliente MQTT que irá usar a conexão Wi-Fi para se comunicar com o broker

//Váriaveis
int valor;
float corrente;

//função para conexão com WiFi
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

//Função para conexão do broker com o mqtt
void reconnect() {
  // Loop até que a conexão com o broker MQTT seja estabelecida
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");  // Exibe no terminal que está tentando conectar ao broker MQTT
    if (client.connect("ESP32_GUSTAVO")) {  // Tenta conectar ao broker MQTT com o nome de cliente "ESP32_GUSTAVO"
      Serial.println("connected");           // Se conectado, imprime "connected" no terminal
    } else {
      Serial.print("failed, rc=");           // Caso falhe na conexão, exibe a mensagem "failed, rc="
      Serial.print(client.state());          // Exibe o código de erro que ocorreu ao tentar a conexão MQTT
      Serial.println(" try again in 5 seconds");  // Exibe a mensagem de tentativas futuras em 5 segundos
      delay(5000);                            // Espera 5 segundos antes de tentar novamente
    }
  }
}

void setup() {
  pinMode(2, OUTPUT);                     // Configura o pino 2 como saída (comum para controle de LED ou outros dispositivos)
  Serial.begin(115200);                   // Inicia a comunicação serial com a taxa de 115200 bauds (velocidade do terminal serial)
  setup_wifi();                           // Chama a função que conecta o ESP32 à rede Wi-Fi
  client.setServer(mqtt_server, 1883);    // Define o endereço IP e a porta (1883) do broker MQTT
  emon1.current(34, 100);                // Current: input pin, calibration.
}

void Conectado() {
  if(WiFi.status()) {                     // Se o status da conexão Wi-Fi for diferente de WL_CONNECTED (indicando que está conectado)
    digitalWrite(2, HIGH);                // Acende o LED no pino 2 (poderia ser um dispositivo ou algo para indicar "conectado")
  } else {                               // Caso contrário, se o ESP32 não estiver conectado
    digitalWrite(2, LOW);                 // Apaga o LED no pino 2 (indicando "desconectado")
  }
}

void ESP32_ENVIA(){
  valor = random(0,100);
  client.publish("RANDOM_GUSTAVO",String(valor).c_str());
  delay(1000);
}

void Leitor_Corrente(){
  corrente = emon1.calcIrms(1480);  // Calculate Irms only
  client.publish("CORRENTE_GUSTAVO", String(corrente).c_str());
  delay(1000);
}

void loop() {
  if (!client.connected()) {              // Se o cliente MQTT não estiver conectado ao broker
    reconnect();                          // Chama a função de reconexão ao broker MQTT
  }
  Conectado();                            // Verifica a conexão Wi-Fi e acende ou apaga o LED dependendo do status
  ESP32_ENVIA();
  Leitor_Corrente();
}
