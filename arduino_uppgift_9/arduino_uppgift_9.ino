int secondPins[] = { 13, 12, 11, 10, 9, 8 };
int minutePins[] = { 7, 6, 5, 4, 3, 2 };
int hourPins[] = { A0, A1, A2, A3, A4 }; 

int seconds = 58;
int minutes = 32;
int hours = 23;

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

  if(hours >= 24) { // 00001100
    hours = 0;
    shutOffLights();
  }

  displaySeconds();
  displayMinutes();
  displayHours();

  Serial.println();
  delay(1000);
}//endloop

/*
 * Lyser upp de röda LED lamporna från pinnarna 8 till 13 för att visa sekunderna på klockan
 */
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

  if(isPlural(seconds)) {
    printSerialValues(seconds, "Sekunder"); 
  } else {
    printSerialValues(seconds, "Sekund");
  }
}

/**
 * Lyser upp de gula LED lamporna från pinnarna 2 till 7 för att visa minuterna på klockan
 */
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

  if(isPlural(minutes)) {
    printSerialValues(minutes, "Minuter"); 
  } else {
    printSerialValues(minutes, "Minut");
  }
}

/**
 * Lyser upp de gröna LED lamporna från pinnarna A0 - A4 (Analog 0 till 7) för att visa timmarna på klockan
 */
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

  if(isPlural(hours)) {
    printSerialValues(hours, "Timmar"); 
  } else {
    printSerialValues(hours, "Timme");
  }
}

/**
 * Skickar tillbaka om nummret är plural eller singular för att hjälpa med att printa grammatiskt 
 * korrekt i Serial Monitor med hjälp av Serial klassen 
 */
bool isPlural(int num) {
  return num < 1 || num > 1;
}

/**
 * Stänger av alla lampor
 */
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

  // Släcker timmlamporna
  for(int i = 0; i < 5; i++) {
    const int pin = hourPins[i];
    digitalWrite(pin, LOW);
  }
}

/**
 * Printar ut alla visare på klockan tillsammans med binära talen
 */
void printSerialValues(int value, String timePrefix){
  Serial.print(" = ");  
  Serial.print(value);
  Serial.print(" ");
  Serial.print(timePrefix);
  Serial.println();
}
