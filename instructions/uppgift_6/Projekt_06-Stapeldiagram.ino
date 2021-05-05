/*******************************************************
   Projekt 6 - Stapeldiagram
 ******************************************************/

// konstanta variabler
const int analogPin = A0; // stiftet till potentiometern.
const int ledSize = 10;  // antalet lysdioder

// en array av stift som lysdioder är anslutna till:
int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };


void setup() {
  // initierar alla stift i arrayen som UTSIGNALER:
  for (int index = 0; index < ledSize; index++) {
    pinMode(ledPins[index], OUTPUT);
  }
  
  Serial.begin(9600);
}

void loop() {
  // potentiometers värde lagras i den lokala variabeln
  int analogValue = analogRead(analogPin);
  
  // mappar resultatet till ett intervall från 0 till 10. 
  int ledLevel = map(analogValue, 0, 1023, 0, ledSize);
  
  Serial.print("analogValue = ");
  Serial.println(analogValue);
  Serial.print("ledLevel = ");
  Serial.println(ledLevel);

  // loopar igenom arrayen:
  for (int index = 0; index < ledSize; index++) {
    // slå på alla stift som index är mindre än ledLevel: 
    if (index < ledLevel) {
      digitalWrite(ledPins[index], HIGH);
    }
    // annars slå av alla andra 
    else {
      digitalWrite(ledPins[index], LOW);
    }
  }
  //delay(1000);
}
