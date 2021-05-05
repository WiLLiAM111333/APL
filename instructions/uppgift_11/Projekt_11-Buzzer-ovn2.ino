/******************************************
  Projekt 11 - Buzzer- ovn2
  När Tryckknappen trycks ner går igång
  piezosummer/buzzer och spelar en melodi.  
********************************************/
// tonerna i melodin: 
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
int melody[] = {262, 196, 196, 220, 196, 0, 247, 262};
 
// tonens längd: 4 = kvarton, 8 = åttonde ton, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
int buzzer = A1; 
int buttonPin = 4;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  
  Serial.begin(9600);
}

void loop() {
  int pushValue = digitalRead(buttonPin);
  Serial.print("pushValue = ");
  Serial.println(pushValue);
  
  if(pushValue == LOW){
    myMelodi();
  }
  else {
    noTone(buzzer);
  }
}

void myMelodi(){ 
  // loopar igenom över meloditoner: 
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // ta en sekund för att beräkna tonens längd
    // dividerat med tontypen.
    // t.ex. kvartton = 1000/4, åttonde ton = 1000/8, etc. 
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // för att skilja tonerna, ställ in en minimitid mellan dem.
    // tonens längd + 30% verkar fungera bra: 
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // sluta spela tonen:
    noTone(buzzer);
  }
}
