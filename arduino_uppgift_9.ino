int secondPins[] = { 13, 12, 11, 10, 9, 8 };
int minutePins[] = { 7, 6, 5, 4, 3, 2 };
int hourPins[] = { A0, A1, A2, A3, A4 };
int seconds = 0;
int minutes = 0;
int hours = 0;

void setup() {
  Serial.begin(9600);

  // Sätter på alla pinnar i output mode
  for(int i = 2; i <= 18; i++) {
    pinMode(i, OUTPUT);
  }
} 

void loop() {
   seconds++;
   
   if(seconds >= 59) { // 111011 binary
    seconds = 0;
    minutes++;
   
  }

  if(minutes >= 59) { // 111011 binary
    minutes = 0;
    hours++;   
  }

  displaySeconds();
  displayMinutes();
  displayHours(); 
/*

  if(hours >= 31) { // 00111111 binary
    shutOffLights();
  }
 
 */ 
  delay(1000);
}//endloop

void displaySeconds() {
  // Storlek på array
  int arraySize = sizeof(secondPins) / sizeof(secondPins[0]);
  
  for(int i = arraySize - 1; i >= 0; i--) {
    // Läser in seconds som en byte och läser en bit på position i
    int currentNumber = bitRead(seconds, i);

    // Skriver en bit från currentNumber (0 eller 1)
    digitalWrite(secondPins[i], currentNumber);

    Serial.print(currentNumber);
  }

serialValues(seconds, " (Sekunder) ");
}

void displayMinutes() {
  // Storlek på arrayen minutePins
  int arraySize = sizeof(minutePins) / sizeof(minutePins[0]);
  
  for(int i = arraySize - 1; i >= 0; i--) {
    // Läser in seconds som en byte och läser en bit på position i
    int currentNumber = bitRead(minutes, i);
    
    // Skriver en bit från currentNumber (0 eller 1)
    digitalWrite(minutePins[i], currentNumber);

    Serial.print(currentNumber);
  }

serialValues(minutes, " (Minuter) ");
}

void displayHours() {
  // Storlek på arrayen minutePins
  int arraySize = sizeof(hourPins) / sizeof(hourPins[0]);
  
  for(int i = arraySize - 1; i >= 0; i--) {
    // Läser in seconds som en byte och läser en bit på position i
    int currentNumber = bitRead(hours, i);
    
    // Skriver en bit från currentNumber (0 eller 1)
    digitalWrite(hourPins[i], currentNumber);

    Serial.print(currentNumber);
  }

serialValues(hours, " (Timmar) ");
Serial.println();

}

void shutOffLights() {
  // Storlek på array secondPins
  int secondsSize = sizeof(secondPins) / sizeof(secondPins[0]);
  // Storlek på array minutePins
  int minutesSize = sizeof(minutePins) / sizeof(minutePins[0]);

  // Släcker minutlamporna
  for(int i = 0; i < minutesSize; i++) {
    digitalWrite(minutePins[i], LOW);
  }
  
  // Släcker sekundlamporna
  for(int i = 0; i < secondsSize; i++) {
    digitalWrite(secondPins[i], LOW);
  }

  for(int i = 0; i < 5; i++) {
    const int pin = hourPins[i];
    digitalWrite(pin, LOW);
  }
}

void serialValues(int timePrefix, String textPrefix){
  Serial.print(" = ");
  Serial.print(timePrefix);
  Serial.print(" ");
  Serial.print(textPrefix);
  Serial.print(" ");
  Serial.println();
}
