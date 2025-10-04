//Saídas
#define LED1 19 // Define que o pino 19 será chamado de LED1
#define LED2 18 // Define que o pino 18 será chamado de LED2
#define LED3 17 // Define que o pino 17 será chamado de LED3
#define LED4 16 // Define que o pino 16 será chamado de LED4
#define LED5 4  // Define que o pino 4 será chamado de LED5
#define LED6 15 // Define que o pino 15 será chamado de LED6

//Variáveis
char Caracter; // Cria uma variável do tipo char chamada Caracter

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial a 115200 bps
  pinMode(LED1, OUTPUT); // Configura o pino 19 (LED1) como saída
  pinMode(LED2, OUTPUT); // Configura o pino 18 (LED2) como saída
  pinMode(LED3, OUTPUT); // Configura o pino 17 (LED3) como saída
  pinMode(LED4, OUTPUT); // Configura o pino 16 (LED4) como saída
  pinMode(LED5, OUTPUT); // Configura o pino 4  (LED5) como saída
  pinMode(LED6, OUTPUT); // Configura o pino 15 (LED6) como saída
}

void loop() {
  Caracter = Serial.read(); // Lê um caractere da porta serial e armazena na variável Caracter

  if (Caracter == 'A') { // Se o caractere for 'A'
    digitalWrite(LED1, HIGH); // Liga o LED1
    Serial.println("LED1 = Ligado"); // Envia mensagem ao monitor serial
  }
  if (Caracter == 'a') { // Se o caractere for 'a'
    digitalWrite(LED1, LOW); // Desliga o LED1
    Serial.println("LED1 = Desligado"); // Envia mensagem ao monitor serial
  }

  if (Caracter == 'B') { // Se o caractere for 'B'
    digitalWrite(LED2, HIGH); // Liga o LED2
    Serial.println("LED2 = Ligado");
  }
  if (Caracter == 'b') { // Se o caractere for 'b'
    digitalWrite(LED2, LOW); // Desliga o LED2
    Serial.println("LED2 = Desligado");
  }

  if (Caracter == 'C') { // Se o caractere for 'C'
    digitalWrite(LED3, HIGH); // Liga o LED3
    Serial.println("LED3 = Ligado");
  }
  if (Caracter == 'c') { // Se o caractere for 'c'
    digitalWrite(LED3, LOW); // Desliga o LED3
    Serial.println("LED3 = Desligado");
  }

  if (Caracter == 'D') { // Se o caractere for 'D'
    digitalWrite(LED4, HIGH); // Liga o LED4
    Serial.println("LED4 = Ligado");
  }
  if (Caracter == 'd') { // Se o caractere for 'd'
    digitalWrite(LED4, LOW); // Desliga o LED4
    Serial.println("LED4 = Desligado");
  }

  if (Caracter == 'E') { // Se o caractere for 'E'
    digitalWrite(LED5, HIGH); // Liga o LED5
    Serial.println("LED5 = Ligado");
  }
  if (Caracter == 'e') { // Se o caractere for 'e'
    digitalWrite(LED5, LOW); // Desliga o LED5
    Serial.println("LED5 = Desligado");
  }

  if (Caracter == 'F') { // Se o caractere for 'F'
    digitalWrite(LED6, HIGH); // Liga o LED6
    Serial.println("LED6 = Ligado");
  }
  if (Caracter == 'f') { // Se o caractere for 'f'
    digitalWrite(LED6, LOW); // Desliga o LED6
    Serial.println("LED6 = Desligado");
  }
}