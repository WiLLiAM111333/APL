/******************************************
  Projekt 11 - Buzzer övn 1
  En buzzer/summer spelar en melodi

  http://www.arduino.cc/en/Tutorial/Tone
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

void setup() { 
}

void loop() {
  // loopar igenom över meloditoner: 
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // ta en sekund för att beräkna tonens längd
    // dividerat med tontypen.
    // t.ex. kvartton = 1000/4, åttonde ton = 1000/8, etc.
    // totala längd=2500 ms 
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // för att skilja tonerna, ställ in en minimitid mellan dem.
    // tonens längd + 30% verkar fungera bra. Totala längd=3250ms
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // sluta spela ljud
    noTone(buzzer);
    // summan av alla totala längder= 5750 ms
  }
}
