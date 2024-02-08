/*
* Haufe
* Sensor de obstáculos para deficientes visuais
* https://github.com/gmasson/haufe
*/

// Carrega a biblioteca Ultrasonic
#include <Ultrasonic.h>

// Define do pino do Arduino conectado ao vibracall
#define PIN_VIBRACALL 2

// Define do pino do Arduino conectado ao buzzer
#define PIN_BUZZER 3

// Define o pino do Arduino a ser utilizado com o pino Trigger do sensor
#define PINO_TRIGGER A0

// Define o pino do Arduino a ser utilizado com o pino Echo do sensor  
#define PINO_ECHO A1

// Inicializa o sensor ultrassônico  
Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO);

// Array com as distâncias em centímetros
const int distancias[] = {30, 60, 90, 120, 150, 180, 210, 240, 270, 300};
const int num_distancias = sizeof(distancias) / sizeof(distancias[0]);

// Frequência padrão do buzzer
const int frequencia_padrao = 2000;

void setup() {  
  pinMode(PIN_VIBRACALL, OUTPUT); // Configura o pino do vibracall como saída
  pinMode(PIN_BUZZER, OUTPUT); // Configura o pino do buzzer como saída
}  

void loop() {  
  float cmMsec;

  // Le os dados do sensor, com o tempo de retorno do sinal  
  long microsec = ultrasonic.timing();

  // Calcula a distancia em centimetros  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  // Emite um sinal vibratório e sonoro com base na distância medida
  for (int i = 0; i < num_distancias; i++) {
    if (cmMsec <= distancias[i]) {
      vibracallSignal(2000);
      buzzerSignal(2000);
      break;
    }
  }
}

void buzzerSignal(int delayTime) {
  tone(PIN_BUZZER, frequencia_padrao); // Emite um som no buzzer na frequência padrão
  delay(delayTime); // Mantém o buzzer ativo pelo tempo especificado
  noTone(PIN_BUZZER); // Desativa o buzzer
}

void vibracallSignal(int delayTime) {
  digitalWrite(PIN_VIBRACALL, HIGH); // Ativa o módulo de vibracall
  delay(delayTime); // Mantém o módulo de vibracall ativo pelo tempo especificado
  digitalWrite(PIN_VIBRACALL, LOW); // Desativa o módulo de vibracall
}
