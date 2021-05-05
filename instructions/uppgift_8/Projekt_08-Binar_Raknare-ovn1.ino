/*******************************************************
*   Projekt 8- Binär Räknare - ovn1
* ******************************************************/
int timer = 100;
int pinArray[]  = {2, 3, 4, 5, 6, 7};
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
  
  if(counter >= 64) {
    counter = 0;
    delay(4000);
    
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
