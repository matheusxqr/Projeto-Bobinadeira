// código que eu fiz no chat e que é uma versão ajustada que possui o controle pwm do motor DC do carretel, e ainda o controle de voltas que o motor deu. 
// caso eu fosse usar esse código e ele funcionar, ainda falta montar o motor do carretel no driver de ponte, alimentado pelo 7805cv, ajustar a velocidade para
// os dois motores andarem sincronizados e vazerem as voltas, além de ajustar o número de voltas por segundo que o motor vai dar e o número máximo de voltas.


const int rpwm = 2; // controle pwm do lado direito do motor 1
const int lpwm = 3; // controle pwm do lado esquerdo do motor 2
const int fcpedal = 4; // fim de curso do pedal
const int fc1 = 5; // fim de curso 1
const int fc2 = 6; // fim de curso 2
const int motorDC = 7; // motor dc ligado pelo driver pra controlar a velocidade dele com pwm

bool motorDireita = false;
bool motorEsquerda = false;
bool motorParado = true;
bool ultimoEstadofc1 = HIGH;
bool ultimoEstadofc2 = HIGH;
bool estadoAtualfc1;
bool estadoAtualfc2;

unsigned long tempoAnterior = 0;  // Variável para armazenar o tempo anterior
int contadorVoltas = 0;  // Variável para contar as voltas do motor
const int limiteVoltas = 150;  // Limite de voltas que o motor pode fazer

void setup() {
  Serial.begin(9600);
  pinMode(fcpedal, INPUT_PULLUP);
  pinMode(fc1, INPUT_PULLUP);
  pinMode(fc2, INPUT_PULLUP);
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(motorDC, OUTPUT);

  digitalWrite(rpwm, 0);
  digitalWrite(lpwm, 0);
  digitalWrite(motorDC, 0);
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
    analogWrite(motorDC, 255); 
  }
  ultimoEstadofc1 = estadoAtualfc1;

  // Lógica de detecção do fim de curso 2 (fc2)
  if (ultimoEstadofc2 == HIGH && estadoAtualfc2 == LOW) {
    Serial.println("FIM DE CURSO 2 PRESSIONADO");
    motorEsquerda = true;  // Motor vai para a esquerda
    motorDireita = false;
    motorParado = false;
    analogWrite(motorDC, 255);
  }
  ultimoEstadofc2 = estadoAtualfc2;

 // Verifica se passou 1 segundo (1000 ms) e se o motor está em movimento
  if (millis() - tempoAnterior >= 1000 && !motorParado) {
    tempoAnterior = millis();  // Atualiza o tempo anterior
    if (contadorVoltas < limiteVoltas) {  // Verifica se ainda não atingiu o limite
      contadorVoltas += 10;  // Incrementa 10 voltas por segundo
      Serial.print("Voltas: ");
      Serial.println(contadorVoltas);  // Exibe o número de voltas
    } else {
      // Se atingiu o limite de voltas, parar o motor
      motorParado = true;
      motorDireita = false;
      motorEsquerda = false;
      analogWrite(motorDC, 0);  // Desliga o motor
      Serial.println("Limite de voltas atingido. Motor desligado.");
    }
  }

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
