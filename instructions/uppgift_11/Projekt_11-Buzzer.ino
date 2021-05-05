/******************************************
  Projekt 11 - Buzzer
  En buzzer/summer skapar enkla ljud. 

  http://www.arduino.cc/en/Tutorial/Tone
********************************************/

int buzzer = 9;

void setup() {
} 

void loop() {
  tone(buzzer, 490);
  delay(200);
  noTone(buzzer);
  delay(100);
}
