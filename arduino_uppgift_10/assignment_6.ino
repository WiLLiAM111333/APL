#include <LiquidCrystal.h>

const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

int seconds = 0;
int minutes = 0;
int hours = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {  
  seconds++;
  
  if(seconds == 60) {
    minutes++;
    seconds = 0;
  }

  if(minutes == 60) {
    hours++;
    minutes = 0;
  }

  if(hours == 24) {
    hours = 0;
  }

  lcd.print(getTimeStr());
  
  delay(1000);
  lcd.clear();
}

/**
 * Formatterar och returnerar en ny sträng för LCD att skriva ut
 */
String getTimeStr() {
  const int ZERO = 0;
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
