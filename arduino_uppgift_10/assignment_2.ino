#include <LiquidCrystal.h>

const int rs = 2;
const int en = 4;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Hello EE19D");
  delay(1000);
}

void loop() {
  for(int i = 0; i < 13; i++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  for(int i = 0; i < 30; i++) {
    lcd.scrollDisplayRight();
    delay(150);
  }

  for(int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
