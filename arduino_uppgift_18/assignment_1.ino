/**********************************************************************
 * Projekt 18-DC-PIR Sensor Rörelsedetektor
 * 
 * LARMSYSTEM
 * Detta projekt simulerar ett larmsystem.
 **********************************************************************/
#define PIN_ON_BUTTON 3    // välj ingångsstift för ON-knappen.
#define PIN_OFF_BUTTON 2    // välj ingångsstift för OFF-knappen.
#define PIN_LED_RED 11   // välj stiftet för den röda lysdioden.             
#define PIN_PIR_SENSOR 12   // välj ingångsstift för PIR-sensor.
#define PIN_BUZZER A0 // // välj stift för buzzer.

int pirSensorState = LOW;       // vi börjar med att ingen rörelse upptäcks.
int pirSensorCheck = LOW;         // variabel för läsning av PIR-sensorns status.

void setup() {
  pinMode(PIN_ON_BUTTON,  INPUT_PULLUP); 
  pinMode(PIN_OFF_BUTTON, INPUT_PULLUP); 
  pinMode(PIN_LED_RED,    OUTPUT);      
  pinMode(PIN_PIR_SENSOR, INPUT);     
  
  Serial.begin(9600);
}

void loop(){
  // Checkar om ON-knappen är intryck:
  if (!digitalRead(PIN_ON_BUTTON)){
    pirSensorState = LOW;
    setAlarm();
    
    delay(100);
  }  
}

void setAlarm() {
  do {
    // läser om PIR-sensor har upptäckt någon rörelse:
    pirSensorCheck = digitalRead(PIN_PIR_SENSOR); 
    
    // Checkar om OFF-knappen är intryck:
    if(!digitalRead(PIN_OFF_BUTTON)) {
      digitalWrite(PIN_LED_RED, LOW); // lysdioden släcks.  
      noTone(PIN_BUZZER);             // buzzern avger inget ljud.
      
      Serial.println("Motion ended!");
      
      pirSensorState = HIGH;      
      delay(100);
      
      break;
    } 
    // Checkar om PIR-sensorn har upptäckt någon rörelse:
    if(pirSensorCheck == HIGH) {
      digitalWrite(PIN_LED_RED, HIGH);  // lysdioden tänds.
      tone(PIN_BUZZER, 440);      // buzzern avger ljud.
    
      Serial.println("Motion detected!");
      
      pirSensorState = LOW;        
      delay(100);
    } 
  } while(!pirSensorState);  
}