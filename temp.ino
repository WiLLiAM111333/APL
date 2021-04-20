#include <LiquidCrystal.h>

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

const int lcdRS = 2;
const int lcdEN = 3;
const int lcdD4 = 6;
const int lcdD5 = 7;
const int lcdD6 = 8;
const int lcdD7 = 9;

const int hourPin = 13;
const int minutePin = 12;
const int celciusPin = 11;

// [0] = Timmar | [1] = Minuter | [2] = Sekunder
int times[3] = { 16, 0, 28 };

// [0] = Timmar | [1] = Minuter | [2] = Sekunder
int wakingTimes[3] = { 16, 0, 30 };

LiquidCrystal lcd(lcdRS, lcdEN, lcdD4, lcdD5, lcdD6, lcdD7);

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(celciusPin, INPUT);
  pinMode(hourPin, INPUT);
  pinMode(minutePin, INPUT);
  pinMode(A5, OUTPUT);
}

void loop() {  
  handleHours();
  handleMinutes();
  handleSeconds();

  times[2]++;

  lcd.print(getTimeStr());
  lcd.setCursor(0, 1);
  lcd.print(toDateString(2021, 4, 19));

  if(validateAlarm()) {
    lcd.clear();
    lcd.print("You are a pirate!");

    // playSong();
  }

  if(digitalRead(hourPin)) {
    times[0]++;
  }

  if(digitalRead(minutePin)) {
    times[1]++;
  }

  if(digitalRead(celciusPin)) {
    lcd.setCursor(0, 2);
    
    String str = "";
    
    const float voltage = getVoltage(celciusPin);
    const float celcius = voltageToCelcius(voltage);
    
    str += celcius;
    str += " Celcius";

    lcd.print(str);
  }

  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
}

/**
 * Formatterar och returnerar en ny sträng för LCD att skriva ut
 */
String getTimeStr() {
  const int ZERO = 0;
  const int hours = times[0];
  const int minutes = times[1];
  const int seconds = times[2];
  
  String str = "";
  
  if(hours < 10) {
    str += ZERO;
  }

  str += hours;
  str += ':';
    
  if(minutes < 10) {
    str += ZERO;
  }

  str += minutes;
  str += ':';
  
  if(seconds < 10) {
    str += ZERO;
  }

  str += seconds;

  return str;
}

/**
 * Kollar om arrayen wakingTimes och times stämmer överens
 */
bool validateAlarm() {
  for(int i = 0; i < 3; i++) {
    if(times[i] != wakingTimes[i]) {
      return false; 
    }

    Serial.print("times[i]: ");
    Serial.print(times[i]);
    Serial.println();
    Serial.print("wakingTimes[i]: ");
    Serial.print(wakingTimes[i]);
    Serial.println();
  }

  return true;
}

/**
 * Fixar med timmar
 */
void handleHours() {
  int hours = times[0];

  if(hours == 24) {
    times[0] = 0;
  }
}

/**
 * Fixar med minuter 
 */
void handleMinutes() {
  int hours = times[0];
  int minutes = times[1];

  if(minutes == 60) {
    times[0]++;
    times[1] = 0;
  }
}

/**
 * Fixar med sekunder
 */
void handleSeconds() {  
  const int seconds = times[2];
  
  if(seconds == 60) {
    times[1]++;
    times[2] = 0;
  }
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}

float voltageToCelcius(float voltage) {
  float fahrenheit = (voltage - 0.5) * 100;
  float celcius = ((fahrenheit - 32) * 5) / 9;
  
  return celcius * 0.66;
}

/*******************************************
           START OF DATE LIBRARY
 ******************************************/

/**
 * Returnerar en sträng formatterad enligt ISO 8601 internatonella standard av åååå/mm/dd
 */
 String toDateString(int years, int months, int days) {
   String str = "Date: ";

   str += years;
   str += '/';

   if(months < 10) {
     str += '0';
   }
   
   str += months;
   
   if(days < 10) {
     days += '0';
   }

   str += '/';
   str += days;

   return str;
 }

void playSong() {
  int notes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,

    NOTE_A4, NOTE_A4,
    //Repeat of first part
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,
    //End of Repeat

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
  };

  // Durations (in ms) of each music note of the song
  // Quarter Note is 250 ms when songSpeed = 1.0
  int durations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125,
    //Rpeat of First Part
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,
    //End of Repeat

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500,

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500
  };

  const int totalNotes = sizeof(notes) / sizeof(int);
  const int buzzer = 15;
  const float songSpeed = 1.0;
  
  for (int i = 0; i < totalNotes; i++) {
    lcd.scrollDisplayLeft();
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
