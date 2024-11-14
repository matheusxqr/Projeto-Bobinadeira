const int rpwm = 2;
const int lpwm = 3;
const int fimdecurso = 4;
const int motorDC = 5;

int estadofimdecurso = 0;    
int ultimoestadofimdecurso = 0;

void setup() {
  Serial.begin(9600);
  pinMode(fimdecurso, INPUT);
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(motorDC, OUTPUT);
  digitalWrite(rpwm, 0);
  digitalWrite(lpwm, 0);
}

void loop() {
  estadofimdecurso = digitalRead(fimdecurso);

  if (fimdecurso == LOW && ultimoestadofimdecurso == HIGH) {
    Serial.println("Fim de curso pressionado!");
    analogWrite(lpwm, 255);
    analogWrite(rpwm, 0);
    analogWrite(motorDC, 255);
    delay(3000);
    analogWrite(rpwm, 255);
    analogWrite(lpwm, 0);
    analogWrite(motorDC, 255);
    delay(3000);
  } 
  else if (estadofimdecurso == HIGH && ultimoestadofimdecurso == LOW) {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
  }

  ultimoestadofimdecurso = estadofimdecurso;
  delay(50);
}
