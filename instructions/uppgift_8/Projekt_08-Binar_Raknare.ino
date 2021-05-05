/*******************************************************
*   Projekt 8- Binär Räknare*
*   Den räknar till nummer 15 med det binära systemet.
*         -------
*         8 4 2 1
*         -------
*         0 0 0 1 = 1
*         0 0 1 0 = 2
*         0 0 1 1 = 3
*         0 1 0 0 = 4
*         0 1 0 1 = 5
*         0 1 1 0 = 6
*         0 1 1 1 = 7
*         1 0 0 0 = 8
*         1 0 0 9 = 9
*         1 0 1 0 = 10
*         1 0 1 1 = 11
*         1 1 0 0 = 12
*         1 1 0 1 = 13
*         1 1 1 0 = 14
*         1 1 1 1 = 15
* ********************************************************/

int timer = 500;
int pinArray[]  = {2, 3, 4, 5};
int sizeOfArray = sizeof(pinArray) / sizeof(pinArray[0]);
int counter;

void setup() {  
  for (int i = 0; i < sizeOfArray; i++) {
    pinMode(pinArray[i], OUTPUT);
  }
  Serial.begin(9600);
  Serial.println();
  Serial.println("The counter starts:");  
}

void loop() {
  counter++;
  
  if(counter >= 16) {
    counter = 0;
    delay(5000);
    
    Serial.println();
    Serial.println("The counter is reset and starts counting again:");  
  }  
  displayCounter();
  
  delay(timer);  
}

void displayCounter() {
  for(int i = sizeOfArray - 1; i >= 0; i--) {
    int currentNumber = bitRead(counter, i);
    digitalWrite(pinArray[i], currentNumber);
    
    Serial.print(currentNumber);
    Serial.print(" ");
  }
  
  Serial.print(" = ");
  Serial.print(counter);
  Serial.println();
} 
