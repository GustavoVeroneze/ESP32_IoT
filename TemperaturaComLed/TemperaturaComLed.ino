int nivel; // Declara a variável 'nivel' que vai armazenar o valor da "temperatura"

// Define que o pino 19 será usado como LED1
#define LED1 19

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial com velocidade de 115200 bps
  pinMode(LED1, OUTPUT); // Configura o pino 19 como saída (para controlar o LED)
}

void loop() {
  nivel = random(0, 100); // Gera um valor aleatório entre 0 e 99 e armazena na variável 'nivel'

  // Envia a "temperatura" simulada para o monitor serial
  Serial.println("Temperatura: " + String(nivel) + "°C");

  // Se a temperatura simulada for maior que 80
  if(nivel > 80){
    digitalWrite(LED1, HIGH); // Liga o LED1 (simulando um alerta de temperatura alta)
  } else {
    digitalWrite(LED1, LOW); // Desliga o LED1 (temperatura normal)
  }

  delay(1000); // Aguarda 1 segundo antes de repetir o processo
}