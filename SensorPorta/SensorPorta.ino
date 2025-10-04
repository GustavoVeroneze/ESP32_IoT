//Entradas, Saídas e Variáveis
//Saídas
#define PORTA 19
#define JANELA 18
//Entrada
#define BT1 33
#define BT2 25
//Variáveis
bool FLAG1 = 0;
bool FLAG2 = 0;
void setup() {
  Serial.begin(115200);
  pinMode(PORTA, OUTPUT);
  pinMode(BT1, INPUT);
  pinMode(JANELA, OUTPUT);
  pinMode(BT2, INPUT);
}

void loop() {
  if (digitalRead(BT1) == 0 && FLAG1 == 0) {
    digitalWrite(PORTA, LOW);
    Serial.println("Porta Fechada");
    FLAG1 = 1;
  }
  if (digitalRead(BT1) == 1 && FLAG1 == 1) {
    digitalWrite(PORTA, HIGH);
    Serial.println("Porta Aberta");
    FLAG1 = 0;
  }
   if (digitalRead(BT2) == 0 && FLAG2 == 0) {
    digitalWrite(JANELA, LOW);
    Serial.println("Janela Fechada");
    FLAG2 = 1;
  }
  if (digitalRead(BT2) == 1 && FLAG2 == 1) {
    digitalWrite(JANELA, HIGH);
    Serial.println("Janela Aberta");
    FLAG2 = 0;
  }
}
