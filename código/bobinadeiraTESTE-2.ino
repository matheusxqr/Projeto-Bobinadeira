// código aqui que eu acredito q vai funcionar, se as ligações estiverem todas corretas. depois só vai faltar configurar o número de voltas e exibir elas no monitor serial, e fazer tudo q 
// eu tinha planejado. talves esse código não funcione, mas aí é só ajustes.


const int rpwm = 2;
const int lpwm = 3;  
const int fcpedal = 4; 
const int fc1 = 5; 
const int fc2 = 6;
// const int motorDC = 7;

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
 //  digitalWrite(motorDC, 0);
}

void loop() {
  
  if (digitalRead(fcpedal) == LOW) {
    Serial.println("PEDAL PRESSIONADO");
    analogWrite(rpwm, 255);  
    analogWrite(lpwm, 0); 
   // analogWrite(motorDC, 255);

    while (digitalRead(fc1) == HIGH && digitalRead(fc2) == HIGH) {
      delay(50); 
    }

    if (digitalRead(fc1) == LOW) {
      Serial.println("FIM DE CURSO 1 PRESIONADO");
      analogWrite(rpwm, 0);  
      analogWrite(lpwm, 255); 
   //   analogWrite(motorDC, 255);
      delay(300); 
    }

    if (digitalRead(fc2) == LOW) {
      Serial.println("FIM DE CURSO 2 PRESSIONADO");
      analogWrite(lpwm, 0); 
      analogWrite(rpwm, 255); 
  // analogWrite(motorDC, 0);
      delay(300);
    }
    
  } 
  else {
    Serial.println("PEDAL SOLTO !!!");
    analogWrite(rpwm, 0); 
    analogWrite(lpwm, 0);
   // analogWrite(motorDC, 0);
  }

  delay(50); 
}
