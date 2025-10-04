#include <WiFi.h>                 // Biblioteca para conectar o ESP32 a uma rede Wi-Fi
#include <PubSubClient.h>         // Biblioteca para comunicação MQTT (publicar/assinar mensagens)

// Atualize com os dados da sua rede Wi-Fi
const char* ssid = "ssid";                 // Nome da rede Wi-Fi
const char* password = "password";         // Senha da rede Wi-Fi
const char* mqtt_server = "your ip";         // Endereço IP do servidor MQTT

// Variáveis para armazenar os dados recebidos via MQTT
String my_topic;                                // Armazena o nome do tópico recebido
String my_payload;                              // Armazena a mensagem (payload) recebida

WiFiClient Gustavo;                             // Cria um cliente Wi-Fi
PubSubClient client(Gustavo);                   // Cria um cliente MQTT usando o cliente Wi-Fi

// Função para conectar o ESP32 ao Wi-Fi
void setup_wifi() {
  delay(10);                                    // Aguarda 10 ms (tempo para estabilização)
  Serial.println();                             // Pula uma linha no monitor serial
  Serial.print("Connecting to ");               // Imprime no serial
  Serial.println(ssid);                         // Mostra o SSID da rede

  WiFi.mode(WIFI_STA);                          // Configura o modo do Wi-Fi como estação (client)
  WiFi.begin(ssid, password);                   // Inicia a conexão com a rede

  while (WiFi.status() != WL_CONNECTED) {       // Aguarda até conectar
    delay(500);                                 // Espera meio segundo
    Serial.print(".");                          // Imprime ponto enquanto conecta
  }

  Serial.println("");                           // Pula linha após conexão
  Serial.println("WiFi connected");             // Confirma conexão
  Serial.print("IP address: ");                 // Exibe IP obtido
  Serial.println(WiFi.localIP());               // Mostra o IP local do ESP32
}

// Função chamada sempre que uma mensagem MQTT for recebida
void callback(char* topic, byte* payload, unsigned int length) {
  String conc_payload;                          // Variável temporária para montar o payload
  for (int i = 0; i < length; i++) {
    conc_payload += ((char)payload[i]);         // Concatena os bytes da mensagem em uma string
  }
  my_topic = topic;                             // Salva o tópico recebido
  my_payload = conc_payload;                    // Salva a mensagem recebida
}

// Função para reconectar ao servidor MQTT
void reconnect() {
  while (!client.connected()) {                 // Enquanto não estiver conectado
    Serial.print("Attempting MQTT connection...");

    if (client.connect("Gustavo")) {            // Tenta se conectar com o nome "Gustavo"
      Serial.println("connected");              // Conectado com sucesso
      client.subscribe("TOP_GUSTAVO");          // Inscreve-se no tópico "TOP_GUSTAVO"
    } else {
      Serial.print("failed, rc=");              // Falha na conexão
      Serial.print(client.state());             // Exibe o código de erro
      Serial.println(" try again in 5 seconds");
      delay(5000);                              // Aguarda 5 segundos antes de tentar novamente
    }
  }
}

// Função de inicialização (executada uma vez após ligar o ESP)
void setup() {
  pinMode(2, OUTPUT);     // Define o pino 2 como saída (geralmente LED embutido)
  pinMode(19, OUTPUT);    // Define o pino 19 como saída
  pinMode(18, OUTPUT);    // Define o pino 18 como saída
  pinMode(17, OUTPUT);    // Define o pino 17 como saída
  pinMode(16, OUTPUT);    // Define o pino 16 como saída

  Serial.begin(115200);   // Inicia a comunicação serial com baud rate de 115200
  setup_wifi();           // Chama a função para conectar ao Wi-Fi
  client.setServer(mqtt_server, 1883);  // Configura o servidor MQTT na porta 1883
  client.setCallback(callback);         // Define a função de callback para mensagens MQTT recebidas
}

// Função que indica se o ESP32 está conectado ao Wi-Fi (acende LED do pino 2)
void conexao() {
  if (WiFi.status()) {
    digitalWrite(2, HIGH);             // Se conectado, acende o LED
  } else {
    digitalWrite(2, LOW);              // Se desconectado, apaga o LED
  }
}

// Função que verifica o payload recebido e ativa/desativa pino 19
void ESP32_RECEBE() {
  if (my_payload == "A") {
    digitalWrite(19, HIGH);           // Se a mensagem for "A", liga o pino 19
    client.publish("Gt_Status1",String("Ligado").c_str());
  }
  if (my_payload == "a") {
    digitalWrite(19, LOW);            // Se a mensagem for "a", desliga o pino 19
    client.publish("Gt_Status1",String("Desligado").c_str());
  }
  if (my_payload == "B") {
    digitalWrite(18, HIGH);           // Se a mensagem for "B", liga o pino 18
    client.publish("Gt_Status2",String("Ligado").c_str());
  }
  if (my_payload == "b") {
    digitalWrite(18, LOW);            // Se a mensagem for "b", desliga o pino 18
    client.publish("Gt_Status2",String("Desligado").c_str());
  }
  if (my_payload == "C") {
    digitalWrite(17, HIGH);           // Se a mensagem for "C", liga o pino 17
    client.publish("Gt_Status3",String("Ligado").c_str());
  }
  if (my_payload == "c") {
    digitalWrite(17, LOW);            // Se a mensagem for "c", desliga o pino 17
    client.publish("Gt_Status3",String("Desligado").c_str());
  }
  if (my_payload == "D") {
    digitalWrite(16, HIGH);           // Se a mensagem for "D", liga o pino 16
    client.publish("Gt_Status4",String("Ligado").c_str());
  }
  if (my_payload == "d") {
    digitalWrite(16, LOW);            // Se a mensagem for "d", desliga o pino 16
    client.publish("Gt_Status4",String("Desligado").c_str());
  }
  if (my_payload == "E") {
    digitalWrite(19, HIGH);
    digitalWrite(18, HIGH);
    digitalWrite(17, HIGH);
    digitalWrite(16, HIGH);           // Se a mensagem for "D", liga o pino 16
    client.publish("Gt_Status1",String("Ligado").c_str());
    client.publish("Gt_Status2",String("Ligado").c_str());
    client.publish("Gt_Status3",String("Ligado").c_str());
    client.publish("Gt_Status4",String("Ligado").c_str());
  }
  if (my_payload == "e") {
    digitalWrite(19, LOW); 
    digitalWrite(18, LOW); 
    digitalWrite(17, LOW); 0
    digitalWrite(16, LOW);            // Se a mensagem for "d", desliga o pino 16
    client.publish("Gt_Status1",String("Desligado").c_str());
    client.publish("Gt_Status2",String("Desligado").c_str());
    client.publish("Gt_Status3",String("Desligado").c_str());
    client.publish("Gt_Status4",String("Desligado").c_str());
  }
}

// Loop principal, executado continuamente
void loop() {
  if (!client.connected()) {          // Se não estiver conectado ao MQTT
    reconnect();                      // Tenta reconectar
  }
  client.loop();                      // Mantém a conexão MQTT ativa e processa mensagens
  conexao();                          // Chama função para verificar conexão Wi-Fi
  ESP32_RECEBE();
}
