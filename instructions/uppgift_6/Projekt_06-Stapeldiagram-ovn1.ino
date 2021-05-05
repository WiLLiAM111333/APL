/************************************************
   Projekt 6 - Stapeldiagram - övn 1
*************************************************/
const int analogPin = A0; 
const int ledSize = 10;  

int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

void setup() {
  for (int index = 0; index < ledSize; index++) {
    pinMode(ledPins[index], OUTPUT);
  }
}

void loop() {
  int analogValue = analogRead(analogPin);
  
  int ledLevel = map(analogValue, 0, 1023, 0, ledSize);

  for (int index = 0; index < ledSize; index+=2) {
    if (index < ledLevel) 
    {
      digitalWrite(ledPins[index], HIGH);
    }
    else {
      digitalWrite(ledPins[index], LOW);
    }
  }
}
