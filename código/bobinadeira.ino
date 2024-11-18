const int rpwm = 2;
const int lpwm = 3;
const int fcpedal = 4;
const int motorDC = 5;

void setup() {
  Serial.begin(9600);
  pinMode(fcpedal, INPUT);
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(motorDC, OUTPUT);
  digitalWrite(rpwm, 0);
  digitalWrite(lpwm, 0);
}

void loop() {
  
 if (digitalRead(fcpedal) == LOW) {
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
  
 if (digitalRead(fcpedal) == HIGH) {
    Serial.println("Fim de curso solto!");
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
  }
  delay(50);
}
