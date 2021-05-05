/************************************************
*  Projekt 5 - Rullande dioder
*
*  Visar användningen av en for-loop.
*  Tänder flera lysdioder i följd och sedan i 
*  omvänd riktning.
 ***********************************************/

// Ju högre tal/värde desto långsammare.
int timer = 500;   

void setup() {
  // tillsätter stift 2 till 7 som UTSIGNAL: 
  for (int pin = 2; pin < 8; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // loopar från lägsta stift till högsta: 
  for (int pin = 2; pin < 8; pin++) {
    // dioden tänds: 
    digitalWrite(pin, HIGH);
    delay(timer);
    
    // dioden släcks: 
    digitalWrite(pin, LOW);
  }

  // loopar från högsta stift till lägsta: 
  for (int pin = 7; pin >= 2; pin--) {
    digitalWrite(pin, HIGH);
    delay(timer);
    
    digitalWrite(pin, LOW);
  }
}
