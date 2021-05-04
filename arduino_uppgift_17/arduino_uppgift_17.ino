/***************************************************************************
*  Projekt 16 - LCD-Game-Nisse
*  Nisse springer i en bana med hinder/kloss som rullar åt vänster
****************************************************************************/
#include <LiquidCrystal.h>

#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587

#define PIN_BUTTON 2
#define PIN_BUTTON_2 3
#define PIN_CRASH_LED 11
#define PIN_AUTOPLAY 1
#define PIN_READWRITE 10
#define PIN_CONTRAST 13
#define PIN_BUZZER A0

#define BLOCK_RUN1 1
#define BLOCK_RUN2 2
#define BLOCK_JUMP 3
#define BLOCK_JUMP_UPPER '.'     //Används tecken '.' för huvudet 
#define BLOCK_JUMP_LOWER 4
#define BLOCK_TRACK_EMPTY ' '    //Användaren tecken ' ' character
#define BLOCK_TRACK_SOLID 5
#define BLOCK_TRACK_SOLID_RIGHT 6
#define BLOCK_TRACK_SOLID_LEFT 7

#define NISSE_HORIZONTAL_POSITION 1    //Horisontell position för hjälten på displayen

#define TRACK_WIDTH 16
#define TRACK_EMPTY 0
#define TRACK_LOWER_BLOCK 1
#define TRACK_UPPER_BLOCK 2

#define NISSE_POSITION_OFF 0          // Nisse är osynlig
#define NISSE_POSITION_RUN_LOWER_1 1  // Nisse springer på nedre raden (position 1) 
#define NISSE_POSITION_RUN_LOWER_2 2  //                                 (position 2)

#define NISSE_POSITION_JUMP_1 3       // Börjar ett hopp
#define NISSE_POSITION_JUMP_2 4       // Halvvägs upp
#define NISSE_POSITION_JUMP_3 5       // Hoppet är på övre raden
#define NISSE_POSITION_JUMP_4 6       // Hoppet är på övre raden
#define NISSE_POSITION_JUMP_5 7       // Hoppet är på övre raden
#define NISSE_POSITION_JUMP_6 8       // Hoppet är på övre raden
#define NISSE_POSITION_JUMP_7 9       // Halvvägs upp
#define NISSE_POSITION_JUMP_8 10      // På väg att landa

#define NISSE_POSITION_RUN_UPPER_1 11 // Nisseen springer på övre raden (position 1))
#define NISSE_POSITION_RUN_UPPER_2 12 //                                (position 2)

// Initiera biblioteket med de stift vi använder.
const int RS = 4;
const int E  = 5;
const int D4 = 7;
const int D5 = 8;
const int D6 = 9;
const int D7 = 10;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

static char trackUpper[TRACK_WIDTH + 1];
static char trackLower[TRACK_WIDTH + 1];
static bool buttonPushed = false;
static bool button2Pushed = false;
static int level;

String difficulties[3] = { "Easy", "Medium", "Hard" };

enum SpeedLevel {
  ONE = 100,
  TWO = 75,
  THREE = 50
};

void rotateArrayRight(String arr[], int amount) {
  for(int i = 0; i < amount; i++) {
    const String temp = arr[i];
    
    if(i + 1 == amount) {
      arr[i] = arr[amount - 1];
      arr[amount - 1] = temp;
    } else {
      arr[i] = arr[i + 1];
      arr[i + 1] = temp;
    }
  }
}

void rotateArrayLeft(String arr[], int amount) {
  for(int i = amount - 1; i >= 0; i--) {
    const String temp = arr[i];
    
    if(i == 0) {
      arr[i] = arr[0];
      arr[0] = temp;
    } else {
      arr[i] = arr[i - 1];
      arr[i - 1] = temp;
    }
  }
}

void difficultySelection(){
  int i = 0;
  bool done = false;
  
  while(!done){
    lcd.setCursor(0, 0);
    lcd.print('>');
    lcd.print(difficulties[i]);
    lcd.setCursor(0, 1);
    
    if(i + 1 == 3){
      i = -1; 
    }
      
    lcd.print(difficulties[i + 1]);
      
    //stoppar loopen och ska starta spelet med den valda svårehetsgraden
    if(buttonPushed){
      done = true;

      const String selectedLevel = difficulties[0];

      if(selectedLevel == "Easy") {
        level = SpeedLevel::ONE;
      } else if(selectedLevel == "Medium") {
        level = SpeedLevel::TWO;
      } else {
        level = SpeedLevel::THREE;
      }
      
      lcd.clear();
      
      buttonPushed = false;
    } else if(button2Pushed){
      lcd.clear();
      rotateArrayRight(difficulties, 3);
      
      button2Pushed = false;
    } 
  }
}

/****************************************************************
* Funktionen skapar Nisse
*****************************************************************/
void createGraphicNisse(){
  static byte graphicNisse[] = {
    // Körläget 1
    B01100,
    B01100,
    B00000,
    B01110,
    B11100,
    B01100,
    B11010,
    B10011,
    // Körläget 2
    B01100,
    B01100,
    B00000,
    B01100,
    B01100,
    B01100,
    B01100,
    B01110,
    // Hopp
    B01100,
    B01100,
    B00000,
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    // Hoppa lägre 
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    // Banan-marken
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    // landa till höger på marken/banan
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    // landa till vänster på marken/banan
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
  };
  
  int i;
  // Hoppa över att använda tecken 0, det gör att lcd.print() kan användas
  // för att rita snabbt flera tecken 
  for (i = 0; i < 7; ++i) {
    lcd.createChar(i + 1, &graphicNisse[i * 8]);
  }
  
  for (i = 0; i < TRACK_WIDTH; ++i) {
    trackUpper[i] = BLOCK_TRACK_EMPTY;
    trackLower[i] = BLOCK_TRACK_EMPTY;
  }
}

/****************************************************************
* Funktionen Skjuter/rullar spelbanan åt vänster.
*****************************************************************/ 
void rollTrackToLeft(char* track, byte newTrack){
  for (int i = 0; i < TRACK_WIDTH; ++i) {
    
    char current = track[i];
    char next = (i == TRACK_WIDTH-1) ? newTrack : track[i+1];
    
    switch (current){
      case BLOCK_TRACK_EMPTY:
        track[i] = (next == BLOCK_TRACK_SOLID) ? BLOCK_TRACK_SOLID_RIGHT : BLOCK_TRACK_EMPTY;
        break;
        
      case BLOCK_TRACK_SOLID:
        track[i] = (next == BLOCK_TRACK_EMPTY) ? BLOCK_TRACK_SOLID_LEFT : BLOCK_TRACK_SOLID;
        break;
        
      case BLOCK_TRACK_SOLID_RIGHT:
        track[i] = BLOCK_TRACK_SOLID;
        break;
        
      case BLOCK_TRACK_SOLID_LEFT:
        track[i] = BLOCK_TRACK_EMPTY;
        break;
    }
  }
}

/*********************************************************************
* Funktionen ritar Nisses olika positioner i spelbanan och scenen.
**********************************************************************/ 
bool drawNisse(byte position, char* trackUpper, char* trackLower, unsigned int score) {
    bool crash = false;
    char upperSave = trackUpper[NISSE_HORIZONTAL_POSITION];
    char lowerSave = trackLower[NISSE_HORIZONTAL_POSITION];
    byte upper, lower;
    
    switch (position) {
      case NISSE_POSITION_OFF:
        upper = lower = BLOCK_TRACK_EMPTY;
        break;
      
      case NISSE_POSITION_RUN_LOWER_1:
        upper = BLOCK_TRACK_EMPTY;
        lower = BLOCK_RUN1;
        break;
      
      case NISSE_POSITION_RUN_LOWER_2:
        upper = BLOCK_TRACK_EMPTY;
        lower = BLOCK_RUN2;
        break;
      
      case NISSE_POSITION_JUMP_1:
      case NISSE_POSITION_JUMP_8:
        upper = BLOCK_TRACK_EMPTY;
        lower = BLOCK_JUMP;
        break;
      
      case NISSE_POSITION_JUMP_2:
      case NISSE_POSITION_JUMP_7:
        upper = BLOCK_JUMP_UPPER;
        lower = BLOCK_JUMP_LOWER;
        break;
      
      case NISSE_POSITION_JUMP_3:
      case NISSE_POSITION_JUMP_4:
      case NISSE_POSITION_JUMP_5:
      case NISSE_POSITION_JUMP_6:
        upper = BLOCK_JUMP;
        lower = BLOCK_TRACK_EMPTY;
        break;
      
      case NISSE_POSITION_RUN_UPPER_1:
        upper = BLOCK_RUN1;
        lower = BLOCK_TRACK_EMPTY;
        break;
      
      case NISSE_POSITION_RUN_UPPER_2:
        upper = BLOCK_RUN2;
        lower = BLOCK_TRACK_EMPTY;
        break;
    }
    
    if (upper != ' ') {
      trackUpper[NISSE_HORIZONTAL_POSITION] = upper;
      crash = !(upperSave == BLOCK_TRACK_EMPTY);
    }
    
    if (lower != ' ') {
      trackLower[NISSE_HORIZONTAL_POSITION] = lower;
      crash |= !(lowerSave == BLOCK_TRACK_EMPTY);
    }
    
    byte digits = (score > 9999) 
      ? 5 
      : (score > 999) 
        ? 4 
        : (score > 99) 
          ? 3 
          : (score > 9) 
            ? 2 
            : 1;
    
    // Ritar scenen
    trackUpper[TRACK_WIDTH] = '\0';
    trackLower[TRACK_WIDTH] = '\0';
    
    char temp = trackUpper[16-digits];
    trackUpper[16-digits] = '\0';
    
    lcd.setCursor(0,0);
    lcd.print(trackUpper);
    trackUpper[16-digits] = temp;  
    lcd.setCursor(0,1);
    lcd.print(trackLower);
    
    lcd.setCursor(16 - digits,0);
    lcd.print(score);
  
    trackUpper[NISSE_HORIZONTAL_POSITION] = upperSave;
    trackLower[NISSE_HORIZONTAL_POSITION] = lowerSave;
    
    return crash;
} //End funktionen drawNisse()


// Funktionen hanterar knapptryckningen som ett avbrott 
void buttonPush() {
  buttonPushed = true;

  Serial.println("buttonPushed");
}

void button2Push() {
  button2Pushed = true;

  Serial.println("button2Pushed");
}

void deathSound() {
  int notes[] = {
    NOTE_G4, 0, NOTE_D5, 0, NOTE_D5, 0,
    NOTE_D5, 0, NOTE_C5, 0, NOTE_B4, 0,
    NOTE_G4, NOTE_E4, 0, NOTE_E4, NOTE_C4,  
  };
  
  int durations[] = {
    80, 60, 100, 250, 60, 60,
    60, 60, 60, 80, 80, 60,
    120, 150, 250, 100, 120
  };
  
  const int totalNotes = sizeof(notes) / sizeof(int);
  const int buzzer = A0;
  const float songSpeed = 1.0;
  
  for (int i = 0; i < totalNotes; i++) {
    const int currentNote = notes[i];
    float wait = durations[i] / songSpeed;
    
    if (currentNote != 0) {
      tone(buzzer, notes[i], wait);
    } else {
      noTone(buzzer);
    }
    
    delay(wait);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_CRASH_LED, OUTPUT);
  
  pinMode(PIN_READWRITE, OUTPUT);
  digitalWrite(PIN_READWRITE, LOW);
  
  pinMode(PIN_CONTRAST, OUTPUT);
  digitalWrite(PIN_CONTRAST, LOW);
  
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);

  pinMode(PIN_BUTTON_2, INPUT);
  digitalWrite(PIN_BUTTON_2, HIGH);
  
  pinMode(PIN_AUTOPLAY, OUTPUT);
  digitalWrite(PIN_AUTOPLAY, HIGH);
  
  // Digital stift 2 mappas för att avbryta 0 PIN_BUTTON 
  attachInterrupt(0, buttonPush, FALLING);
  
  // Digital stift 3 mappas flr att avbryta 1 PIN_BUTTON_2
  attachInterrupt(1, button2Push, FALLING);
  
  createGraphicNisse();
  
  lcd.begin(16, 2);
}

void loop() {
  // Refreshar lcd cursor till position 0, 0 för att se till att menyn alltid printar ut från rad 1 till 2 om man dör
  lcd.setCursor(0, 0);
  
  while(!level) {
    difficultySelection();
  }

  lcd.clear();
  
  static byte nissePos  = NISSE_POSITION_RUN_LOWER_1;
  static byte newTrackType = TRACK_EMPTY;
  static byte newTrackDuration = 1;
  static bool playing = false;
  static bool blink   = false;
  static unsigned int distance = 0;
  
  if (!playing) {     
    drawNisse((blink) ? NISSE_POSITION_OFF : nissePos, trackUpper, trackLower, distance >> 3);

    if(blink) {
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("*GAME NISSE*");
      delay(1000);
      lcd.clear();
      lcd.print("TRYCK START");
    }

    delay(500);
    blink = !blink;
    
    if(buttonPushed) {
      createGraphicNisse();
      nissePos = NISSE_POSITION_RUN_LOWER_1;
      playing = true;
      buttonPushed = false;
      distance = 0;
    }

    return;
  }

  // Spelbanan rullar åt vänster
  rollTrackToLeft(trackLower, newTrackType == TRACK_LOWER_BLOCK ? BLOCK_TRACK_SOLID : BLOCK_TRACK_EMPTY);
  rollTrackToLeft(trackUpper, newTrackType == TRACK_UPPER_BLOCK ? BLOCK_TRACK_SOLID : BLOCK_TRACK_EMPTY);
  
  // Skapa ny spelbana för att komma in till höger 
  if (--newTrackDuration == 0) {
    if (newTrackType == TRACK_EMPTY) {
      newTrackType = (random(3) == 0) ? TRACK_UPPER_BLOCK : TRACK_LOWER_BLOCK;
      newTrackDuration = 2 + random(10);
    } else {
      newTrackType = TRACK_EMPTY;
      newTrackDuration = 10 + random(10);
    }
  }
    
  if (buttonPushed) {
    if (nissePos <= NISSE_POSITION_RUN_LOWER_2) nissePos = NISSE_POSITION_JUMP_1;
    
    buttonPushed = false;
  } 
  
  // Spelaren krachar med en block/något. Jäklar!
  if (drawNisse(nissePos, trackUpper, trackLower, distance >> 4)) {
    lcd.clear();
    lcd.print("...CRASH...!");

    digitalWrite(PIN_CRASH_LED, HIGH);
    deathSound();

    level = 0;
    
    delay(2000); 
    
    lcd.clear();
    digitalWrite(PIN_CRASH_LED, LOW);
    buttonPushed = false;
    
    createGraphicNisse();
    nissePos = NISSE_POSITION_RUN_LOWER_1;
    playing = false;
  } else {
    if (nissePos == NISSE_POSITION_RUN_LOWER_2 || nissePos == NISSE_POSITION_JUMP_8) {
      nissePos = NISSE_POSITION_RUN_LOWER_1;
    } else if ((nissePos >= NISSE_POSITION_JUMP_3 && nissePos <= NISSE_POSITION_JUMP_5) && trackLower[NISSE_HORIZONTAL_POSITION] != BLOCK_TRACK_EMPTY) {
      nissePos = NISSE_POSITION_RUN_UPPER_1;
    } else if (nissePos >= NISSE_POSITION_RUN_UPPER_1 && trackLower[NISSE_HORIZONTAL_POSITION] == BLOCK_TRACK_EMPTY) {
      nissePos = NISSE_POSITION_JUMP_5;
    } else if (nissePos == NISSE_POSITION_RUN_UPPER_2) {
      nissePos = NISSE_POSITION_RUN_UPPER_1;
    } else {
      ++nissePos;
    }
    
    ++distance;
    
    digitalWrite(PIN_AUTOPLAY, trackLower[NISSE_HORIZONTAL_POSITION + 2] == BLOCK_TRACK_EMPTY ? HIGH : LOW);
  }
  delay(level ? level : 0);
}