/******************************************
    Projekt 4 - Potentiometer övn 1 
*******************************************/

// Variabler
int sensorPin = A0;   
int ledPin13  = 13;    
int ledPin5   = 5;    
int sensorValue = 0;

void setup() 
{
  pinMode(ledPin13, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  
  // för att visa info/data på monitorn.
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
  
  // visar data på monitorn
  Serial.print("sensorValue13 = ");
  Serial.print(sensorValue);
  Serial.println(" millisekunder");
  
  Serial.print("sensorValue5 = ");
  Serial.print(sensorValue/5);
  Serial.println(" millisekunder");
  
  digitalWrite(ledPin13, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin13, LOW);
  delay(sensorValue); 
  
  digitalWrite(ledPin5, HIGH);
  delay(sensorValue/5);
  digitalWrite(ledPin5, LOW);
  delay(sensorValue/5);  
}
