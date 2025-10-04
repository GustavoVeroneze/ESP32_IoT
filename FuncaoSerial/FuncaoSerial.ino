//Definição de Entradas, Saídas e Variáveis
//Saídas
#define LED1 19
#define LED2 18
#define LED3 17
#define LED4 16
#define LED5 4
#define LED6 15
//Entradas

//Variáveis
char Caracter;

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
}

void tudo_ligado() {
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED3, HIGH);
  delay(1000);
  digitalWrite(LED4, HIGH);
  delay(1000);
  digitalWrite(LED5, HIGH);
  delay(1000);
  digitalWrite(LED6, HIGH);
}

void tudo_desligado() {
  digitalWrite(LED1, LOW);
  delay(1000);
  digitalWrite(LED2, LOW);
  delay(1000);
  digitalWrite(LED3, LOW);
  delay(1000);
  digitalWrite(LED4, LOW);
  delay(1000);
  digitalWrite(LED5, LOW);
  delay(1000);
  digitalWrite(LED6, LOW);
}

void loop() {
  Caracter = Serial.read();

  if (Caracter == 'B') {
    Serial.println("Ligando LEDS...");
      tudo_ligado();
    Serial.println("Todos os LEDS estão ligados");
  }
  if (Caracter == 'b') {
    Serial.println("Desligando LEDS...");
      tudo_desligado();
    Serial.println("Todos os LEDS estão desligados");
  }
}
