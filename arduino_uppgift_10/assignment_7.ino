#include <LiquidCrystal.h>

const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

// [0] = Timmar | [1] = Minuter | [2] = Sekunder
int times[3] = { 16, 0, 28 };

// [0] = Timmar | [1] = Minuter | [2] = Sekunder
int wakingTimes[3] = { 16, 0, 30 };

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {  
  times[2]++;

  validateHours();
  validateMinutes();
  validateSeconds();

  lcd.print(getTimeStr());

  if(validateAlarm()) {
    lcd.clear();
    lcd.print("WAKE UP!");

    // Kan förlängas... 5 sek för testing
    delay(5000);
  }

  delay(1000);
  lcd.clear();
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

bool validateAlarm() {
  for(int i = 0; i < 3; i++) {
    if(times[i] != wakingTimes[i]) {
      return false; 
    }
  }

  return true;
}

void validateHours() {
  int hours = times[0];

  if(hours == 24) {
    times[0] = 0;
  }
}

void validateMinutes() {
  int hours = times[0];
  int minutes = times[1];

  if(minutes == 60) {
    times[0]++;
    times[1] = 0;
  }
}

void validateSeconds() {  
  const int seconds = times[2];
  
  if(seconds == 60) {
    times[1]++;
    times[2] = 0;
  }
}
