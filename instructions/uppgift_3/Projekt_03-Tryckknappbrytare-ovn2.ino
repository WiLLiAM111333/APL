/******************************************* 
*  Projekt 3 - Tryckknappbrytare övn 2
********************************************/

// Konstanta variabler har fast värde som INTE ändras 
const int buttonPinRed = 2;
const int buttonPinYellow = 7;
const int ledPinRed = 12;
const int ledPinYellow = 13; 

// vanliga variabler ändrar värde under exekveringen
int buttonStateRed = 0; 
int buttonStateYellow = 0;

void setup() {
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(buttonPinRed, INPUT);
  pinMode(buttonPinYellow, INPUT);
}

void loop() {
  // läser om tryckknappen är intryck eller inte:
  buttonStateRed    = digitalRead(buttonPinRed);
  buttonStateYellow = digitalRead(buttonPinYellow);

  
  if (buttonStateRed == HIGH) {
    digitalWrite(ledPinRed, HIGH); 
  }
  else if (buttonStateYellow == HIGH) {
     digitalWrite(ledPinYellow, HIGH); 
  } 
  else {
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, LOW);
  }
}
