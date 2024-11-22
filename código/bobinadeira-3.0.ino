const int rpwm = 2;
const int lpwm = 3;  
const int fcpedal = 4; 
const int fc1 = 5; 
const int fc2 = 6;
// const int motorDC = 7;

bool motorDireita = false;
bool motorEsquerda = false;
bool motorParado = true;
bool ultimoEstadofc1 = HIGH;
bool ultimoEstadofc2 = HIGH;
bool estadoAtualfc1;
bool estadoAtualfc2;

void setup() {
  Serial.begin(9600);
  pinMode(fcpedal, INPUT_PULLUP);
  pinMode(fc1, INPUT_PULLUP);
  pinMode(fc2, INPUT_PULLUP);
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
//  pinMode(motorDC, OUTPUT);

  digitalWrite(rpwm, 0);
  digitalWrite(lpwm, 0);
 //  digitalWrite(motorDC, 0);
}

void loop() {
  // Lê o estado atual dos botões de fim de curso
  estadoAtualfc1 = digitalRead(fc1);
  estadoAtualfc2 = digitalRead(fc2);

  // Lógica para o pedal
  if (digitalRead(fcpedal) == HIGH) {
    Serial.println("PEDAL SOLTO");
    motorParado = true;  // Se o pedal estiver solto, o motor para
    motorDireita = false;
    motorEsquerda = false;
  } else {
    Serial.println("PEDAL PRESSIONADO");
    motorParado = false;  // Se o pedal estiver pressionado, o motor pode girar
  }

  // Lógica de detecção do fim de curso 1 (fc1)
  if (ultimoEstadofc1 == HIGH && estadoAtualfc1 == LOW) {
    Serial.println("FIM DE CURSO 1 PRESIONADO");
    motorDireita = true;  // Motor vai para a direita
    motorEsquerda = false;
    motorParado = false;
  }
  ultimoEstadofc1 = estadoAtualfc1;

  // Lógica de detecção do fim de curso 2 (fc2)
  if (ultimoEstadofc2 == HIGH && estadoAtualfc2 == LOW) {
    Serial.println("FIM DE CURSO 2 PRESSIONADO");
    motorEsquerda = true;  // Motor vai para a esquerda
    motorDireita = false;
    motorParado = false;
  }
  ultimoEstadofc2 = estadoAtualfc2;

  // Controle do motor com base nas variáveis
  if (motorDireita) {
    analogWrite(rpwm, 255);  
    analogWrite(lpwm, 0);
  } else if (motorEsquerda) {
    analogWrite(rpwm, 0);  
    analogWrite(lpwm, 255); 
  } else if (motorParado) {
    analogWrite(rpwm, 0);  
    analogWrite(lpwm, 0); 
  }

  delay(50);  // Delay para evitar leituras rápidas demais
}
