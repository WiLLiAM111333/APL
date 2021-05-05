/*************************************************
    Projekt 4 - Potentiometer  
**************************************************/

// Variabler
int sensorPin = A0;   // stift-värdet för potentiometer.
int ledPin = 13;      // stift-värdet för lysdioden.
int sensorValue = 0;  // för att lagra värde från sensorPin. 

void setup() 
{
  // funktionen ställer in ledPin-variabeln som UTSIGNAL:
  pinMode(ledPin, OUTPUT);
  
  // för att visa info/data på monitorn.
  Serial.begin(9600);
}

void loop() 
{
  // funtionen läser värdet från stiftet sensorPin och  
  // lagrar det i sensorValue-variabeln.
  sensorValue = analogRead(sensorPin);
  
  // visar data på monitorn
  Serial.print("sensorValue = ");
  Serial.print(sensorValue);
  Serial.println(" millisekunder");
  
  // funktionen slår på lysdioden.
  digitalWrite(ledPin, HIGH);
  
  // funktionen stoppar programmet med antalet millisekunder 
  // som finns lagrad i sensorValue-variabeln.
  delay(sensorValue);
  
  // funktionen slår av lysdioden.
  digitalWrite(ledPin, LOW);
  
  delay(sensorValue);
}
