/**********************************************************
* Projekt 13 - Servo-Motor
* Potentiometer styr servo-motors rotation/varv
***********************************************************/

 // bibliotek <Servo.h> används för att styra med dess funktioner servo-motor.
#include <Servo.h>

Servo servo_9;

void setup()
{
  Serial.begin(9600);
  
  servo_9.attach(9);
}

void loop()
{
  // map funktionen omvandlar signaler från potentiometer 0-1023
  // till 0-180 grader vinkel(angle).
  int angle = map(analogRead(A1), 0, 1023, 0, 180);
  
  Serial.print("Angle = ");
  Serial.println(angle);
  
  servo_9.write(angle);
  delay(10);
}
