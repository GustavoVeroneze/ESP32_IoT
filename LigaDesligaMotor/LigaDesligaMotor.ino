//Definição de Entradas, Saídas e Variáveis
//Entradas
#define BL 33
#define BD 25
//Saídas
#define MOTOR 19
//Variáveis
bool FLAG1 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BL, INPUT);
  pinMode(BD, INPUT);
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  if (digitalRead(BL) == 0 && FLAG1 == 0) {
    digitalWrite(MOTOR, HIGH);
    Serial.println("Motor = Ligado");
    FLAG1 = 1;
  }
  if (digitalRead(BD) == 0 && FLAG1 == 1) {
    digitalWrite(MOTOR, LOW);
    Serial.println("Motor = Desligado");
    FLAG1 = 0;
  }
}
