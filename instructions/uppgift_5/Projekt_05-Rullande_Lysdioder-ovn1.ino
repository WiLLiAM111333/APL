/************************************************
*  Projekt 5 - Rullande dioder - övn 1
 ***********************************************/

int timer = 1300;   

void setup() { 
  for (int pin = 2; pin < 8; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() { 
  for (int pin = 2; pin < 8; pin+=2) { 
    digitalWrite(pin, HIGH);
    delay(timer); 
    digitalWrite(pin, LOW);
  }
 
  for (int pin = 6; pin >= 2; pin-=2) {
    digitalWrite(pin, HIGH);
    delay(timer); 
    digitalWrite(pin, LOW);
  }
}
