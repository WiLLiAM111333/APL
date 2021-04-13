#include <LiquidCrystal.h>

const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const String names[] = {
  "William",
  "Kasper",
  "Adrian",
  "Elias",
  "Nam",
  "Gustav",
  "Linus",
  "David",
  "Reza",
  "Kevin",
  "Marcus",
  "Ismail",
  "Max",
  "Rahmatullah",
  "Sebastian",
  "Herman",
  "Arthur",
  "Ilia",
  "Alex",
  "Iman-Danis",
  "Atrin",
  "Ardwan",
  "Benjamin",
  "Eric",
   "Vincent"
 };

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {  
  int cursorPos = 0;
  
  for(int i = 0; i < 25; i++) {
    for(int k = 0; k < names[i].length(); k++) {
      const char letter = names[i][k];

      lcd.print(letter);
      cursorPos++;
      lcd.setCursor(cursorPos, 0);

      delay(100);
    }

    delay(750);
    cursorPos = 0;
    lcd.clear();
  }
  
  lcd.clear();
}