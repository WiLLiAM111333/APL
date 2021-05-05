/*
 Tryckknappbrytaren
 
 Slår på och av en lysdiod (LED) ansluten till digital
 stift 13, när du trycker på en tryckknappbrytare fäst 
 på stift 2.
 
 Kretsen:
  * LED(Lysdioden) ansluten från stift 13 till jorden (GND)
  * tryckknapp fäst på stift 2 från + 5V
  * 1K motstånd fäst till stift 2 från jorden(-)
 */

// Konstanta variabler har fast värde som INTE ändras 
const int buttonPin = 2;   // numret på tryckknappbrytares stift.
const int ledPin =  13;    // numret på lysdiodens stift.

// vanliga variabler ändrar värde under exekveringen:
int buttonState = 0;    // variabeln läser tryckknappens värde

void setup() {
  // sätter in lysdiodens stift som UTSIGNAL:
  pinMode(ledPin, OUTPUT);
  // sätter in tryckknappbrytaren stift som INSIGNAL:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // läser om tryckknappen är intryck eller inte:
  buttonState = digitalRead(buttonPin);

  // checkar om tryckknappen är intryck.
  // om det är det, är tyckknappens HIGH=1:
  if (buttonState == HIGH) {
    // lysdioden tänds:
    digitalWrite(ledPin, HIGH);
  } else {
    // lysdioden släcks:
    digitalWrite(ledPin, LOW);
  }
}
