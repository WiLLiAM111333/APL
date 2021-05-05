/*************************************************************************
* Projekt 13 - Servo motor övn1
*
* Fototransistor som är ljusberoende styr och kontrollerar både servo-motor 
* och lysdioderna.
* Ja, det blir en simulering av en kontroll lampa för stranden.
**************************************************************************/

// bibliotek <Servo.h> används för att styra med dess funktioner servo-motor.
#include <Servo.h>

// med den här objekt kommer man att kunna anropa en del funktioner från Servo.h
Servo servo_9;

const int LED_GREEN = 6;
const int LED_YELLOW = 5;
const int LED_RED = 4;

void setup()
{
  Serial.begin(9600);
  
  servo_9.attach(9);
  
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  int sensor = analogRead(A0);
  
  // visar värdet på sensorn på monitor(konsol-fönstret).
  Serial.print("sensor = ");
  Serial.println(sensor);
  
  // om sensoren är mindre än 15 tänds den gröna lysdioden och motor roterar 20 grader.
  if(sensor < 15 ) // låg
  {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    servo_9.write(20);
    delay(10);
  }
  
  // om sensoren är större än 14 och mindre än 26, tänds den gula lysdioden och motor roterar 90 grader.
  if(sensor > 14 && sensor < 26 ) // normal
  {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    servo_9.write(90);
    delay(10);
  }
  
  // om sensoren är större än 25 tänds den röda lysdioden och motor roterar till 150 grader.
  if(sensor > 25 ) // hög
  {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    servo_9.write(150);
    delay(10);
  }
}
